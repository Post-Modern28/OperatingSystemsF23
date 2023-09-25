#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int const_tri(int* p, int n){
    if (n == 0) return 0;
    if (n < 3) return 1;
    *p = 0;
    *(p+1) = 1;
    *(p+2) = 1;
    n -= 2;
    while (n > 0){
        *(p+2) = *(p+2) + *(p+1) + *p;
        *p = *(p+2) - *(p+1) - *p;
        *p = *p + *(p+1);
        *(p+1) = *p - *(p+1);
        *p = *p - *(p+1);
        n--;
    }
    return *(p+2);
}

int main() {
    const int x = 1;
    const int *q = &x;

    int* const p = (int*)malloc(3*sizeof(int));
//    *p = 32;
//    *(p + 1) = *p;
//    *(p + 2) = 2*(*p);
    p[0] = 32;
    p[1] = p[0];
    p[2] = 2*p[0];


    printf("Memory address of cell 1: %p\n", &p[0]);
    printf("Memory address of cell 2: %p\n", &p[1]);
    printf("Memory address of cell 3: %p\n", &p[2]);
    printf("Value of cell 1: %d\n", *p);
    printf("Value of cell 2: %d\n", *(p+1));
    printf("Value of cell 3: %d\n", *(p+2));

    for (int i=0; i < 20; i++){
        printf("Tribonacci(%d): %d\n", i, const_tri(p, i));
    }

    free(p);

    return 0;
}