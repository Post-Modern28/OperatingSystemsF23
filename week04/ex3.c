#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]){
	int n = atoi(argv[1]);
	for (int i = 0; i < n; i++){
		int x = fork();
		sleep(5);
		if (x == -1){
			return 1;
		}
	}

return 0;
}
