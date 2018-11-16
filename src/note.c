//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#include "note.h"

#define PIN_SPEAKER 0

void note_init(void) {
	DDRB |= (1<<PIN_SPEAKER);
}

void note_play(byte temp_note) {
	TCNT0 = 0x00;
	if (temp_note > 100) {
		OCR0A = temp_note;
		TCCR0B |= (1<<CS01)+(1<<CS00);
		TCCR0A |= (1<<COM0A0) + (1<<WGM01);
	}
}

void note_stop(void) {
	TCCR0A &= ~((1<<COM0A0) + (1<<WGM01));
	TCCR0B &= ~((1<<CS01)+(1<<CS00));
	PORTB &= ~(1<<PIN_SPEAKER);
}
