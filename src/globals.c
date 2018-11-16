//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#include "globals.h"

volatile byte is_data_received;
volatile byte data_read;
volatile byte data_write;

byte EEMEM eeprom_song_written;
d_word EEMEM eeprom_song[75];
