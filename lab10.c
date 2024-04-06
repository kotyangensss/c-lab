#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float *distance(float dots[][2], int n) {
    float **dist;
    dist = (float **) malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        dist[i] = (float *) malloc((n - 1) * sizeof(float));
    }
    for (int i = 0; i < n; i++) {
        int k = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                dist[i][k] = sqrt(pow(dots[i][0] - dots[j][0], 2) + pow(dots[i][1] - dots[j][1], 2));
            } else { k--; }
            k++;
        }
    }
    return dist;
}

int *split(int num) {
    int copy = num;
    int size = 0;
    while (copy > 0) {
        size++;
        copy /= 10;
    }
    int *a;
    a = (int *) malloc((size + 1) * sizeof(int));
    a[size] = -1;
    int counter = size - 1;
    while (num > 0) {
        a[counter] = num % 10;
        num /= 10;
        counter--;
    }
    return a;
}

int main() {
    int n;
    scanf("%d", &n);
    float dots[n][2];
    for (int i = 0; i < n; i++) {
        scanf("%f", &dots[i][0]);
        scanf("%f", &dots[i][1]);
    }
    float **dist = distance(dots, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-1; j++) {
            printf("%f ", dist[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        free(dist[i]);
    }
    free(dist);
    int num;
    scanf("%d", &num);
    int *arr = split(num);
    int i = 0;
    while (arr[i]!=-1) {
        printf("%d ", arr[i]);
        i++;
    }
    free(arr);
}