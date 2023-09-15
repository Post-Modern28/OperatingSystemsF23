#include <stdio.h>
#include <string.h>
#include <ctype.h>


int count(char s[] , char letter){
    int count = 0;
    for (int i = 0; i < strlen(s); i++){
        if (tolower(s[i]) == letter){
            count++;
        }
    }
    return count;
}

void countAll(char s[]){
    char arr[] = "qwertyuiopasdfghjklzxcvbnm";
    for (int i = 0; i < 26; i++){
        int x = count(s, arr[i]);
        if (x){
            printf("%c: %d  ", arr[i], x);
        }
    }
}

int main(){
    char s[256];
    printf("Enter your string: \n");
    fgets(s, 256, stdin);
    countAll(s);
}

