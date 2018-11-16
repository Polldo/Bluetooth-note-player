//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#ifndef NOTE_PLAYER_H
#define NOTE_PLAYER_H

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/atomic.h>
#include "globals.h"
#include "note.h"

void note_player_init(void);

void note_player_start(void);

void note_player_stop(void);

upd_note_func note_player_update;

#endif
