//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#include "button.h"

#include "note_transfer.h"

#define CMD_ESC 0
#define CMD_PLAY 0x01
#define CMD_TRANS 0x02
#define	CMD_DISABLE_EEPROM 0x03
#define	CMD_ENABLE_EEPROM 0x04
#define TIMEOUT_CMD 10000
#define TIMEOUT_PLAY 5000
#define RESPONSE_START 0x40
#define RESPONSE_OK 0x65
#define RESPONSE_EXIT 0xF0
#define END_NOTE 0xFFFF //the end note must be double contained in a d_word

#ifndef EEPROM_WRITTEN
#define EEPROM_WRITTEN 0x00
#endif
#ifndef EEPROM_ERASED
#define EEPROM_ERASED 0xFF
#endif

extern byte EEMEM eeprom_song_written;
extern d_word EEMEM eeprom_song[75];
static void note_transfer_play(void);
static word note_transfer_prepare_buffer(word *buffer);
static void note_transfer_song_read(void);
static void note_transfer_song_disable(void);
static void note_transfer_song_enable(void);

void note_transfer_init(void) {
	uart_init();
	note_init();
	uart_listen();
}

void note_transfer_stop(void) {
	uart_listen_stop();
}

byte note_transfer_is_started(void) {
	byte feedback = uart_data_received_feedback();
	if (feedback) {
		uart_data_read();
		uart_data_write(RESPONSE_START);
	}
	return feedback;
}

void note_transfer(void) {
	byte end_transfer = 0;
	while ((!end_transfer) && uart_timed_wait_data(TIMEOUT_CMD)) {
		switch(uart_data_read()) {
			case CMD_ESC: {
				end_transfer = 1;
				uart_data_write(RESPONSE_EXIT);
				break;
			}
			case CMD_PLAY: {
				uart_data_write(RESPONSE_OK);
				note_transfer_play();
				uart_data_write(RESPONSE_EXIT);
				break;
			}
			case CMD_TRANS: {
				uart_data_write(RESPONSE_OK);
				note_transfer_song_read();
				uart_data_write(RESPONSE_EXIT);
				break;
			}		
			case CMD_DISABLE_EEPROM: {
				uart_data_write(RESPONSE_OK);
				note_transfer_song_disable();
				uart_data_write(RESPONSE_EXIT);
				break;
			}	
			case CMD_ENABLE_EEPROM: {
				uart_data_write(RESPONSE_OK);
				note_transfer_song_enable();
				uart_data_write(RESPONSE_EXIT);
				break;
			}	
			default: {
				break;
			}
		}
	}
	if (!end_transfer) {
		uart_data_write(RESPONSE_EXIT);
	}
}

static void note_transfer_play(void) {
	byte note = 0;
	while (note != 0xff && uart_timed_wait_data(TIMEOUT_PLAY)){
		note_stop();
		note = uart_data_read();
		note_play(note);
	}
	note_stop();
}

static word note_transfer_prepare_buffer(word *buffer) {
	word byte_counter = 0;	
	word note = 0;
	while (note != END_NOTE && byte_counter < 147) {
		note = uart_wait_word();
		buffer[byte_counter++] = note;
		buffer[byte_counter++] = uart_wait_word();
	}
	//adding the END NOTE to the buffer
	if (note != END_NOTE) {
		buffer[byte_counter++] = END_NOTE;
		buffer[byte_counter++] = END_NOTE;
	}
	return byte_counter * 2;
}

static void note_transfer_song_read(void) {
	word buffer[150];
	word byte_counter = note_transfer_prepare_buffer(buffer);
	eeprom_update_block((void*)buffer, (void*)eeprom_song, byte_counter);
	eeprom_update_byte(&eeprom_song_written, EEPROM_WRITTEN);
}

static void note_transfer_song_disable(void) {
	eeprom_update_byte(&eeprom_song_written, EEPROM_ERASED);
}

static void note_transfer_song_enable(void) {
	eeprom_update_byte(&eeprom_song_written, EEPROM_WRITTEN);
}
