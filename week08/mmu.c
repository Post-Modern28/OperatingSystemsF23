#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>
#include "pte.h"


PTE* page_table;

void sigusr1_handler(int signo){
	;
}

int main(int argc, char *argv[]) {
 	int PAGE_SIZE = atoi(argv[1]);
 	pid_t pager_id = atoi(argv[argc-1]);
 	int fd;
 	double hits = 0, overall = 0;
 	
 	fd = open("/tmp/ex2/pagetable", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
 	page_table = (PTE*) mmap(NULL, sizeof(PTE) * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
 	
 	
	char* str = argv[2];
    char* command = strtok(str, " "); 
	signal(SIGUSR1, sigusr1_handler);
	
    while (command != NULL) {
    	++overall;
        char operation_type = command[0];
        int page_num = atoi(&command[1]);
        //printf("%c %d\n", operation_type, page_num);
        if (page_num > PAGE_SIZE){
        	printf("ALARM!!!!\n");
        	printf("%d %d\n", page_num, PAGE_SIZE);
        	return 1;
        }
        
 		if (operation_type == 'W'){
 				page_table[page_num].dirty = true;
 			}
 		if (!page_table[page_num].valid){
 			printf("Page %d is not loaded in RAM\n", page_num);
 			
 			page_table[page_num].referenced = getpid();
 			
 			kill(pager_id, SIGUSR1);
 			pause(); 
 		}
 		else{
 			printf("Page %d is already loaded in RAM\n", page_num);
 			
 			++hits;
 		}
 		
        command = strtok(NULL, " ");
        
        
    }
 	
 	close(fd);
 	printf("Hit rate is %f", hits/overall);
    
}

