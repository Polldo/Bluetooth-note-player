//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#include "button.h"

#ifndef NOTE_TRANSFER_H
#define NOTE_TRANSFER_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include "globals.h"
#include "uart.h"
#include "note.h"

void note_transfer_init(void);

void note_transfer_stop(void);

byte note_transfer_is_started(void);

void note_transfer(void);

#endif
