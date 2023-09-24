#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

void* aggregate(void* base, size_t size, int n, void* initial_value, void* (*opr)(const void*, const void*)) {
    void* result = initial_value;

    for(int i=0; i<n; i++) {
        result = opr(result, base + i*size);
    }
    return result;
}

void* addi(const void* a, const void* b) {
    int* sum = (int*) malloc(sizeof(typeof(*a)));
    *sum = *(int*)a + *(int*)b;
    return sum;
}
void* addf(const void* a, const void* b) {
    double* sum = (double*) malloc(sizeof(double));
    *sum = *(double*)a + *(double*)b;
    return sum;
}



void* multiplyi(const void* a, const void* b) {
    int* product = (int*) malloc(sizeof(typeof(*a)));
    *product = *(int*)a * *(int*)b;
    return product;
}

void* multiplyf(const void* a, const void* b) {
    double* product = (double*) malloc(sizeof(double));
    *product = *(double*)a * *(double*)b;
    return product;
}

void* maxi(const void* a, const void* b) {
    int* max = (int*) malloc(sizeof(int));
    *max = *(int*)a > *(int*)b ? *(int*)a : *(int*)b;
    return max;
}

void* maxf(const void* a, const void* b) {
    double* max = (double*) malloc(sizeof(double));
    *max = *(double*)a > *(double*)b ? *(double*)a : *(double*)b;
    return max;
}


int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    double arr2[] = {1.2, 3.4, 5.6, 7.8, 9.0};
    int x = 0;
    int* p = &x;
    double y = 0;
    double* q = &y;
    int* sum = (int*) aggregate(arr1, sizeof(int), 5, p, addi);
    double* sum2 =  (double*) aggregate(arr2, sizeof(double), 5, q, addf);
    printf("Sum of elements in arr1: %d\n", *sum);
    printf("Sum of elements in arr2: %f\n", *sum2);
    x = 1;
    y = 1;
    int* product = (int*) aggregate(arr1, sizeof(int), 5, p, multiplyi);
    double* product2 = (double*) aggregate(arr2, sizeof(double), 5, q, multiplyf);
    printf("Product of elements in arr1: %d\n", *product);
    printf("Product of elements in arr2: %f\n", *product2);
    x = INT_MIN;
    y = -DBL_MAX;
    int* max_val = (int*) aggregate(arr1, sizeof(int), 5, p, maxi);
    double* max_val2 = (double*) aggregate(arr2, sizeof(double), 5, q, maxf);
    printf("Max value in arr1: %d\n", *max_val);
    printf("Max value in arr2: %f\n", *max_val2);

    free(sum);
    free(product);
    free(max_val);
    free(sum2);
    free(product2);
    free(max_val2);
    free(q);
    free(p);

    return 0;
}
