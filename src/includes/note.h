//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#ifndef NOTE_H
#define NOTE_H

#include <avr/io.h>
#include "globals.h"

void note_init(void);

void note_play(byte temp_note);

void note_stop(void);

#endif
