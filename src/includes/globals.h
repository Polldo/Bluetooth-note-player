//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#ifndef GLOBALS_H
#define GLOBALS_H

#ifndef EEPROM_WRITTEN
#define EEPROM_WRITTEN 0x00
#endif
#ifndef EEPROM_ERASED
#define EEPROM_ERASED 0xFF
#endif

#include <avr/io.h>
#include <avr/eeprom.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t d_word;

typedef void (*upd_note_func)(d_word millis_now);

extern volatile byte is_data_received;
extern volatile byte data_read;
extern volatile byte data_write;

extern byte EEMEM eeprom_song_written;
extern d_word EEMEM eeprom_song[75];

#endif
