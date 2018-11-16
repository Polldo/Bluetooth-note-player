#include <stdio.h>
#include <string.h>
#define CLK 8000000.0
#define PRESCALER 64.0

int note_to_freq(char *note) {
	int freq;
	if(!strcmp(note, "C4") || !strcmp(note, "DO4")) {
    	freq = 262;
	}
	else if(!strcmp(note, "D4") || !strcmp(note, "RE4")) {
		freq = 294;
	}
	else if(!strcmp(note, "E4") || !strcmp(note, "MI4")) {
		freq = 330;
	}
	else if(!strcmp(note, "F4") || !strcmp(note, "FA4")) {
		freq = 349;
	}
	else if(!strcmp(note, "G4") || !strcmp(note, "SOL4")) {
		freq = 392;
	}
	else if(!strcmp(note, "A4") || !strcmp(note, "LA4")) {
		freq = 440;
	}	
	else if(!strcmp(note, "B4") || !strcmp(note, "SI4")) {
		freq = 494;
	}
	else if(!strcmp(note, "C5") || !strcmp(note, "DO5")) {
		freq = 523;
	}
	else if(!strcmp(note, "D5") || !strcmp(note, "RE5")) {
		freq = 587;
	}
	else if(!strcmp(note, "E5") || !strcmp(note, "MI5")) {
		freq = 659;
	}
	else if(!strcmp(note, "F5") || !strcmp(note, "FA5")) {
		freq = 740;
	}
	else if(!strcmp(note, "PAUSE")) {
		freq = 0;
	}
	else {
 		freq = 0;
	}
	if (freq != 0) 
		freq = (CLK/(freq*2.0*PRESCALER) - 1); 
	return freq;
}

int duration_to_msec(int bpm, int duration) {
	return (60000.0 / bpm * 4.0 / duration);	
}

int main(void) {
	int bpm;
	scanf("%d", &bpm);
	char note[6];
	int duration;
	int note_list[200];
	int duration_list[200];
	int number_note = 0;
	scanf(" %s %d", note, &duration);
	while(strcmp(note,"x")) {
		note_list[number_note] = note_to_freq(note);
		duration_list[number_note] = duration_to_msec(bpm, duration);
		number_note += 1;
		if(0){//if(duration > 4) {
			duration = (60000.0 / bpm - duration_list[number_note - 1]);
			note_list[number_note] = note_to_freq("PAUSE");
			duration_list[number_note] = duration;
			number_note += 1;
		}
		scanf(" %s %d", note, &duration);
	}
	for(int index = 0; index < number_note - 1; index++) {
		printf("%d, %d, ", note_list[index], duration_list[index]);
	}
	printf("%d, %d", note_list[number_note - 1], duration_list[number_note - 1]);
}
