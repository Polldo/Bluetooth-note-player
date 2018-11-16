//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#include <avr/io.h>
#include <avr/interrupt.h>
#include "globals.h"
#include "milliseconds.h"
#include "button.h"
#include "note_player.h"
#include "note_transfer.h"
#include "led.h"

typedef enum {PLAY_INIT, PLAY, TRANSFER_INIT, TRANSFER, TRANSFER_END} sys_state;
static sys_state state = PLAY_INIT;

int main(void) {
//init
	while(1) {
	//loop
		switch(state) {
			case PLAY_INIT: {
				note_player_init();
				button_init();
				milliseconds_start();
				state = PLAY;
				break;
			}
			case PLAY: {
				note_player_update(milliseconds_get());
				button_update(milliseconds_get());
				if(button_is_pressed()) {
					state = TRANSFER_INIT;
					milliseconds_stop();
					note_player_stop();
				}
				break;
			}
			case TRANSFER_INIT: {
				note_transfer_init();
				milliseconds_start();
				button_init();
				state = TRANSFER;
				break;
			}
			case TRANSFER: {
				if(note_transfer_is_started()) {
					milliseconds_stop();
					note_transfer();
					state = TRANSFER_END;
				} else {
					button_update(milliseconds_get());
					if(button_is_pressed()) {
						milliseconds_stop();
						state = TRANSFER_END;
					}
				}				
				break;
			}
			case TRANSFER_END: {
				note_transfer_stop();
				state = PLAY_INIT;	
				break;
			}
		}
	}
}


