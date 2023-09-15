#include <stdio.h>
#include <string.h>
#include <ctype.h>


void printRectangle(int n, int m){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            printf("*");
        }
        printf("\n");
    }
    printf("\n\n");
}

void printRightTriangle(int n){
    for (int i = 1; i <= n; i++){
        for (int j = 0; j < i; j++){
            printf("*");
        }
        printf("\n");
    }

    printf("\n\n");
}

void printTriangle(int n){
    if (n % 2 != 1){
        printf("Set an odd n");
        return;
    }
    for (int i = 0; i < n/2+1; i++){
        for (int j = -1; j < i; j++){
            printf("*");
        }
        printf("\n");
    }
    for (int i = n/2; i > 0; i--){
        for (int j = 0; j < i; j++){
            printf("*");
        }
        printf("\n");
    }
    printf("\n\n");
}


int main(){
    printRectangle(6, 5);
    printRightTriangle(7);
    printTriangle(7);
}

