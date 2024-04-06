#include <stdio.h>

int main() {
    int num1, range, num2;
    scanf ("%d", &num1);
    range = num1 >= 1 && num1 <= 100;
    switch (range){
        case 0 :
            printf ("%s\n", "Не входит в диапазон");
            break;
        case 1 :
            printf ("%s\n", "Входит в диапазон");
            break;
    }
    scanf ("%d", &num2);
    printf ("%d", (num2 >> 1) & 1);
}
