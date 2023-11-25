#include <stdio.h>
#include <linux/input.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


#define N 120
int main(){
	int fp;
	printf("Starting\n");
	fp = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
	if (fp < 0){
		printf("Error opening file");
		exit(1);
	}
	struct input_event ev;
	int prev = -1;
	int prev_val = -1;
	int prev_prev = -1;
	char char_pressed[N];
	unsigned char char_repeated[N];
	for (int i = 0; i < N; i++){
		char_pressed[i] = 0;
		char_repeated[i] = 0;
	}
	printf("List of available hotkeys:\n1)C+A+P\n2)P+E\n3)O+S\n4)P+Y\n5)V+P+N\n6)E+X\n");
	while(1){
		read(fp, &ev, sizeof(struct input_event));
		if (ev.type == EV_KEY){
			if (char_pressed[18] && char_pressed[45]){
				printf("E+X combination is pressed, breaking\n");
				break; 
			}
			
			if (char_pressed[18] && char_pressed[25] && !(char_repeated[18] && char_repeated[25])){
				printf("I passed the exam!\n");
			}
			
			if (char_pressed[24] && char_pressed[31] && !(char_repeated[24] && char_repeated[31])){
				printf("I love Operating Systems course!\n");
			}
			
			if (char_pressed[25] && char_pressed[21] && !(char_repeated[25] && char_repeated[21])){
				printf("Python is the best language in the world!\n(After C and C++, of course)\n");
			}
			
			if (char_pressed[25] && char_pressed[30] && char_pressed[46] && !(char_repeated[25] && char_repeated[30] && char_repeated[46])){
				printf("Get some cappucino!\n");
			}
			
			if (char_pressed[25] && char_pressed[47] && char_pressed[49] && !(char_repeated[25] && char_repeated[47] && char_repeated[49])){
				printf("Download Cheburnet, best VPN service in Russia! Link: https://4ebur.net\n");
			}
			
			
			if (ev.value == 1){
				printf("\nPRESSED  character 0x%04x(%d)\n", ev.code, ev.code);
				prev = 1;
				char_pressed[ev.code] = 1;
			}
			if (ev.value == 0){
				prev = 0;
				printf("\nRELEASED character 0x%04x(%d)\n", ev.code, ev.code);
				char_pressed[ev.code] = 0;
				char_repeated[ev.code] = 0;
			}
			if (ev.value == 2 && prev == 1){
				prev = 2;
				printf("REPEATING CHARACHTER 0x%04x(%d)\n", ev.code, ev.code);
				char_repeated[ev.code] = 1;
			}
			for (int i = 0; i < N; i++){ // I added this cycle because previous conditional branch may not always work (if 2 charachters were pressed and held simultaneously)
				if (char_pressed[i] && i != ev.code){
					char_repeated[i] = 1;
				}
			}
			prev_prev = prev_val;
			prev_val = ev.code;
			
			
		}
		
	}
	close(fp);
	printf("Finished\n");
}
