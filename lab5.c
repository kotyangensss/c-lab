#include <stdio.h>

int main() {
    int array[7] = {23, 5678, 2, 564, 365, 77, 443};
    for (int i = 0; i < 7;i++){
        printf("%d - %d\n",i+1,array[i]);
    }
    int n = 2;
    int matrix1[2][2] = {{1, 0},
                         {1, 4}};
    int matrix2[2][2] = {{1, 2},
                         {0, 1}};
    int matrix[2][2];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
            for (int k = 0; k < n; k++) {
                matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
