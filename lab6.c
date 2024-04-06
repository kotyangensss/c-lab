#include <stdio.h>
#include <malloc.h>

int main() {
    const int N = 4;
    double array[N];
    double *arr;
    array[0] = 56.4;
    array[1] = 36.5;
    array[2] = 7.7;
    array[3] = 44.3;
    for (int i = 0; i < N; i++){
        printf("%2.1f ", array[i]);
    }
    printf("\n");
    arr = (double*)malloc(N * sizeof(double));
    arr[0] = 56.4;
    arr[1] = 36.5;
    arr[2] = 7.7;
    arr[3] = 44.3;
    for (int i = 0; i < N; i++){
        printf("%2.1f ", arr[i]);
    }
    free(arr);
}
