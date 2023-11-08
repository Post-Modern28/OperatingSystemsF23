#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include "pte.h"


int PAGE_SIZE;
int FRAME_SIZE;

char** DISK;
char** RAM;

PTE* page_table;
int RAM_load = 0;

int (*search_function)(PTE* page_table);


void update_page_on_disk(int page_num){
	DISK[page_num][0] = 'U';
} 


void load_on_RAM(int cell,int page_num){
	int mmu_pid = page_table[page_num].referenced;
	page_table[page_num].frame = cell;
	page_table[page_num].valid = true;
	page_table[page_num].referenced = 0;
	kill(mmu_pid, SIGUSR2);
}
 
 
void swap_from_RAM(int cell, int page_num){
	page_table[page_num].frame = -1;
	page_table[page_num].valid = false;
	page_table[page_num].reference_count = 0;
    if (page_table[page_num].dirty){
    	update_page_on_disk(page_num);
    	page_table[page_num].dirty = false;
    } 
}


int random_pick(PTE* page_table){
		int rand_idx = rand() % FRAME_SIZE;
		for (int i = 0; i < PAGE_SIZE; i++){
			if (page_table[i].frame == rand_idx){
				return i;
			}
				
		}
	}
	
	
int nfu(PTE* page_table){
	int min_ref_num, indx;
	for (int i = 0; i < PAGE_SIZE; i++){
		if (page_table[i].valid && page_table[i].reference_count < min_ref_num){
			min_ref_num = page_table[i].reference_count;
			indx = i;
		}
	}
	return indx;
}	

int aging(PTE* page_table){
	int min_age, indx;
	for (int i = 0; i < PAGE_SIZE; i++){
		if (page_table[i].valid && page_table[i].count < min_age){
			min_age = page_table[i].count;
			indx = i;
		}
	}
	return indx;
}

	
void sigusr1_handler(int signo) {
    for (int i = 0; i < PAGE_SIZE; i++){
    	if (page_table[i].referenced && !page_table[i].valid){
    		if (RAM_load < FRAME_SIZE){
    			load_on_RAM(RAM_load, i);
    			++RAM_load;
    		}
    		else{
    			int j = search_function(page_table);
    			int cell = page_table[j].frame;
    			swap_from_RAM(cell, j);
    			load_on_RAM(cell, i);	
    		}
    	break;
    	}
    }
    
}
int main(int argc, char *argv[]) {

    if (argc != 4) {
        return 1;
    }
    
    PAGE_SIZE = atoi(argv[1]);
    FRAME_SIZE = atoi(argv[2]);
    char* search_type = argv[3];
    printf("%s\n", search_type);
    if (strcmp(search_type, "random") == 0){
    	search_function = random_pick;
    }
    else if (strcmp(search_type, "nfu") == 0){
    	search_function = nfu;
    }
    else if (strcmp(search_type, "aging") == 0){
    	search_function = aging;
    }
    else{
    	printf("uncknown algorithm, setting random as default\n");
    	search_function = random_pick;
    }

    DISK = malloc(PAGE_SIZE * sizeof(char));
    
    RAM = malloc(FRAME_SIZE * sizeof(char));
    for (int i = 0; i < PAGE_SIZE; i++){
    	DISK[i] = malloc(8 * sizeof(char));
    }
    for (int i = 0; i < FRAME_SIZE; i++){
    	RAM[i] = malloc(8 * sizeof(char));
    }
    
    mkdir("/tmp/ex2", 0666);
    int fd = open("/tmp/ex2/pagetable", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    ftruncate(fd, sizeof(PTE)*PAGE_SIZE);
    page_table = (PTE*) mmap(NULL, sizeof(PTE) * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    signal(SIGUSR1, sigusr1_handler);
    
    for (int i = 0; i < PAGE_SIZE; i++) {
        page_table[i].valid = false;
        page_table[i].frame = -1;
        page_table[i].dirty = false;
        page_table[i].referenced = 0;
        page_table[i].reference_count = 0;
        page_table[i].count = 0;
    }
    printf("Pager pid is %d\n", getpid());
    
    while (1){
    	pause();
    }
    close(fd);
	return 0;
}
