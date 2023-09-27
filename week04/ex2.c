#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define N 120

int main(){
	FILE *fp;
	char filename[] = "temp.txt";
	fp = fopen(filename, "w");
	fclose(fp);
	int u[N];
	int v[N];
	for (int i = 0; i < N; i++){
		u[i] = rand() % 100;
		v[i] = rand() % 100;
		//printf("%d %d \n", u[i], v[i]);
	}
	int n;
	printf("Enter n: ");
	scanf("%d", &n);
	int id = getpid();
	for (int i = 1; i < n; i++){
		if (getpid() == id){
			if (fork() == -1){
				return 4;
			}
		}
	}
	
	int seg = getpid() % n;
	int rat = 120 / n;
	
	fp = fopen(filename, "a");
	if (fp == NULL) { 
        return 2;
    }
    int dp = 0;
    printf("Process %d computes cells %d-%d \n", getpid(), rat * seg, rat * seg + rat-1);
    for (int i = rat * seg; i < rat * seg + rat; i++){
    	dp += v[i] * u[i];
    }
    fprintf(fp, "%d ", dp);
    fclose(fp);
    if (getpid() == id){
		sleep(2);
		int summary = 0;
		fp = fopen(filename, "r");
		if (fp == NULL) { 
        	return 2;
    	}
    	int count = 0;
    	int num;
    	while (fscanf(fp, "%d", &num) == 1 && count < n) { 
        summary += num;
        count++;
    	}	
    	printf("Dot product is %d\n", summary);
	}
	return 0;
}
