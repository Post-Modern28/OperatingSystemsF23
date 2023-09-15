#include <stdio.h>


long convert(long num, int source, int target){
	if (source < 2 || source > 10 || target < 2 || target > 10 || num < 0){
	    printf("Cannot convert! \n");
	    return -1;
	}
    char arr[1000];
    int p = 0;
    long to_dec = 0;
    if (source != 10){
    	long power = 1; 
    	while (num != 0){
    	    long last_digit = num % 10;
    	    to_dec += last_digit * power;
    	    num /= 10;
    	    power *= source;
    	}
    }
    else{
    	to_dec = num;
    }
    if (target == 10){
    	return to_dec;
    }
    while(to_dec != 0){
    	int digit = to_dec % target;
    	char new_digit = digit + '0';
    	arr[p++] = new_digit;
    	to_dec /= target;
    }
    for (int i = 0; i < p/2; i++){
    	int tmp = arr[i];
    	arr[i] = arr[p-i-1];
    	arr[p-i-1] = tmp;
    }
    sscanf(arr, "%ld", &num);
    return num;
}


int main(){
	long number;
	int n_src, n_tgt;
	printf("Enter your number: ");
	scanf("%ld", &number);
	printf("Indicate the source system: ");
	scanf("%d", &n_src);
	printf("Choose the target system: ");
	scanf("%d", &n_tgt);
	printf("%ld", convert(number, n_src, n_tgt));
	
}
