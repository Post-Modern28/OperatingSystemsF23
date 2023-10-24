# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
#include <stdint-gcc.h>
#include <string.h>
#include <time.h>
#define N 10000000
unsigned int* arr;


void allocate_first_fit(unsigned int adr, int size){
    int lp=0, rp=0, counter=0;
    while (rp < N){
        if (!arr[rp]){
            ++counter;
        } else{
            counter = 0;
            lp = rp+1;
        }
        if (counter == size){
            while (lp != rp){
                arr[lp++] = adr;
            }
            break;
        }


        rp++;
    }
}
void allocate_best_fit(unsigned int adr, int size){
    int lp=0, rp=0, counter=0;
    int diff = N;
    int best_block_idx = -1;
    while (rp < N){
        if (!arr[rp]){
            ++counter;
        } else{
            if ((counter >= size) && (counter - size < diff)){
                best_block_idx = lp;
            }
            counter = 0;
            lp = rp+1;
        }
        rp++;
    }
    if (best_block_idx != -1){
        for (int i = best_block_idx; i < best_block_idx+size; i++){
            arr[i] = adr;
        }
    }
}


void allocate_worst_fit(unsigned int adr, int size){
    int lp=0, rp=0, counter=0;
    int diff = -1;
    int best_block_idx = -1;
    while (rp < N){
        if (!arr[rp]){
            ++counter;
        } else{
            if ((counter >= size) && (counter - size > diff)){
                best_block_idx = lp;
            }
            counter = 0;
            lp = rp+1;
        }
        rp++;
    }
    if (best_block_idx != -1){
        for (int i = best_block_idx; i < best_block_idx+size; i++){
            arr[i] = adr;
        }
    }
}


void clear(unsigned int addr){
    for (int i = 0; i < N; i++){
        if (arr[i] == addr){
            while (arr[i] == addr){
                arr[i++] = 0;
            }

            break;

        }
    }
}

int main(int argc, char *argv[]){

    FILE *fp;
    char line[100];
    clock_t start, end;
    double cpu_time_used;
    for (int i = 0; i < 3; i++){
        arr = (unsigned int*) calloc(N, sizeof(int));
        if (i == 0){
            printf("First fit: \n");
        }
        else if (i == 1){
            printf("Best fit: \n");
        }
        else{
            printf("Worst fit: \n");
        }

        //fp = fopen("C:\\Users\\test\\CLionProjects\\for_OS_Course\\queries.txt", "r");
        fp = fopen("queries.txt", "r");
        if (fp == NULL) {
            printf("Error opening file\n");
            return 1;
        }
        start = clock();
        double query_size = 0;
        while (fgets(line, sizeof(line), fp)) {
            query_size++;
            if (strcmp(line, "end\n") == 0) {
                break;
            }
            char *token = strtok(line, " ");
            if (strcmp(token, "allocate") == 0) {
                int address, size;
                token = strtok(NULL, " ");
                address = atoi(token);
                token = strtok(NULL, " ");
                size = atoi(token);
                if (i == 0){
                    allocate_first_fit(address, size);
                }else if (i == 1){
                    allocate_best_fit(address, size);
                }else{
                    allocate_worst_fit(address, size);
                }

            } else if (strcmp(token, "clear") == 0) {
                int id;
                token = strtok(NULL, " ");
                id = atoi(token);
                clear(id);
            }
        }

        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("Execution time: %f seconds\n", cpu_time_used);
        printf("Throughput: %f queries/sec\n", query_size/ cpu_time_used);
        fclose(fp);
    }

    return 0;
}





