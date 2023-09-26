#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>




int* QuickSort(int arr[], int size){
    if (size <= 1){
        return arr;
    }
    int* less = NULL;
    //int* equal = NULL;
    int* greater = NULL;
    int l_s=0, e_s=0, g_s = 0;
    int pivot = arr[size/2];
    for (int i = 0; i < size; i++){
        if (arr[i] < pivot){
            if (less == NULL){
                less = (int*) malloc(++l_s * sizeof(int));
            }
            else{
                less = (int*)realloc(less, ++l_s * sizeof(int));
            }

            less[l_s-1] = arr[i];
        }
        else if (arr[i] == pivot){
            ++e_s;
//            if (equal == NULL){
//                equal = (int*) malloc(++e_s);
//            }
//            else{
//                equal = realloc(equal, ++e_s);
//            }
//            equal[e_s-1] = arr[i];
        }
        else{
            if (greater == NULL){
                greater = (int*) malloc(++g_s * sizeof(int));
            }
            else{
                greater = (int*) realloc(greater, ++g_s * sizeof(int));
            }
            greater[g_s-1] = arr[i];
        }
    }
    less = QuickSort(less, l_s);
    greater = QuickSort(greater, g_s);
    int k = 0;
    int* new_arr = (int*) malloc(size * sizeof(int));
    for (int i = 0; i < l_s; i++){
        new_arr[k++] = less[i];
    }
    for (int i = 0; i < e_s; i++){
        new_arr[k++] = pivot;
    }
    for (int i = 0; i < g_s; i++){
        new_arr[k++] = greater[i];
    }
    free(less);
    free(greater);

    return new_arr;

}


int main(){
    int n = 10;
    int* arr = (int*) malloc(n);
    arr[0] = 5;
    arr[1] = 3;
    arr[2] = 1;
    arr[3] = 4;
    arr[4] = 4;
    arr[5] = 10;
    arr[6] = 8;
    arr[7] = 9;
    arr[8] = 5;
    arr[9] = 7;
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    arr = QuickSort(arr, n);
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    free(arr);
}