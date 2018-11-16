//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#include "note_player.h"

#define LAST_NOTE 0xFF
#define PAUSE_NOTE 0x00
#define LAST_PAUSE_DURATION 500 //PAUSE_DURATION_AFTER_LAST_NOTE

#ifndef EEPROM_WRITTEN
#define EEPROM_WRITTEN 0x00
#endif
#ifndef EEPROM_ERASED
#define EEPROM_ERASED 0xFF
#endif

static byte note_offset;
static const word notes[20] PROGMEM = {
	238,500,212,1000,238,1000,238,1000,0x00FF
};
extern byte EEMEM eeprom_song_written;
extern d_word EEMEM eeprom_song[75];
static d_word millis_note_start;
static d_word millis_note_duration;
static void note_eeprom_update(d_word millis_now);
static void note_rom_update(d_word millis_now);

void note_player_init(void) {
	note_init();
	millis_note_start = 0;
	millis_note_duration = 0;
	note_offset = 0;
	note_player_update = &note_rom_update;
	if (eeprom_read_byte(&eeprom_song_written) == EEPROM_WRITTEN) 
		note_player_update = &note_eeprom_update;
}

void note_player_stop(void) {
	note_stop();
}

static void note_eeprom_update(d_word millis_now) {
	if (millis_now - millis_note_start >= millis_note_duration) {
		note_stop();
		word eeprom_notes[2];
		eeprom_read_block((void*)eeprom_notes, (void*)(&(eeprom_song[note_offset++])), 4);
		byte next_note = (byte) eeprom_notes[0];
		if (next_note == LAST_NOTE) {
			note_offset = 0;
			millis_note_start = millis_now;
			millis_note_duration = LAST_PAUSE_DURATION; 
		} else {
			note_play(next_note);
			millis_note_start = millis_now;
			millis_note_duration = (d_word) eeprom_notes[1];
		}
	}
}

static void note_rom_update(d_word millis_now) {
	if (millis_now - millis_note_start >= millis_note_duration) {
		note_stop();
		byte next_note = (byte) pgm_read_word(&(notes[note_offset++]));
		if (next_note == LAST_NOTE) {
			note_offset = 0;
			millis_note_start = millis_now;
			millis_note_duration = LAST_PAUSE_DURATION; 
		} else {
			note_play(next_note);
			millis_note_start = millis_now;
			millis_note_duration = (d_word) pgm_read_word(&(notes[note_offset++]));
		}
	}
}


