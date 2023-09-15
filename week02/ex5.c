#include <stdio.h>

unsigned long tribonacci(unsigned int n){
    if (!n) return 0;
    if (n < 3) return 1;
    unsigned long t1, t2, t3;
    t1 = 0;
    t2 = 1;
    t3 = 1;
    for (unsigned int i = 3; i < n; ++i){
    	unsigned long tmp = t3;
    	t3 = t1 + t2 + t3;
    	t1 = t2;
    	t2 = tmp;
   
    }
    return t3;  
}


int main(){
	printf("Tribonnaci(4): %lu \nTribonnaci(36): %lu", tribonacci(4), tribonacci(36));
}
