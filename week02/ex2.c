#include <stdio.h>


int main(){
    char arr[1000];
    fgets(arr, 1000, stdin);
    int p = 0;
    for (; p < 1000; p++){
        if (arr[p] == '.' || arr[p] == '\n' || arr[p] == '\0'){
            break;
        }
    }
    char rev[p+2];
    rev[0] = '"';
    for (int i = 1; i <= p; i++){
        rev[i] = arr[p-i];
    }
    rev[p+1] = '"';
    printf("%s", rev);
}

