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


int main(int argc, char *argv[]) {
 	int PAGE_SIZE = atoi(argv[1]);
 	pid_t pager_id = atoi(argv[argc-1]);
 	int fd;
 	
 	fd = open("/tmp/ex2/pagetable", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
 	page_table = (PTE*) mmap(NULL, sizeof(PTE) * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
 	
 	
	char* str = argv[2];
    char* command = strtok(str, " "); 

    while (command != NULL) {
        char operation_type = command[0];
        int page_num = atoi(&command[1]);
 		if (operation_type == 'W'){
 				page_table[page_num].dirty = true;
 			}
 		if (!page_table[page_num].valid){
 			printf("Page %d is not loaded in RAM\n", page_num);
 			
 			page_table[page_num].referenced = 1;
 			
 			kill(pager_id, SIGUSR1);
 		}
 		else{
 			printf("Page %d is already loaded in RAM\n", page_num);
 		}
        command = strtok(NULL, " ");
        sleep(1);
    }
 	for (int i = 0; i < argc-1; i++){
 		printf("%s", argv[i]);
 		char* command = argv[i];
 		
 	
 	}
 	close(fd);
 	
    
}

