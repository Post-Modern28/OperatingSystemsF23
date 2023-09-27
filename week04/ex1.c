#include <stdio.h>
#include <unistd.h>
#include <time.h>
int main(){
	clock_t t = clock();

	int pid2;
	int pid1 = fork();
	    if (pid1 == -1){
	    	return 1;
	    }
	    if (pid1 == 0){
	    	t = clock();
	    }
	    else{
	    	int pid2 = fork();
	    }
	    if (pid2 == -1){
	    	return 1;
	    }
	    if (pid2 == 0){
	    	t = clock();
	    }
	    sleep(5);
	    t = clock()-t;
	    printf("Process id: %d | Parent id: %d | Finished in %ld ticks\n", getpid(), getppid(), t);
    

    
    return 0;

}
