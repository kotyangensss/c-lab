#include <stdio.h>

int main() {
    int cost_m, cost, num, over, number;
    printf("Введите месячную плату, минутную и кол-во минут\n");
    scanf("%d%d%d", &cost_m, &cost, &num);
    over = (num - 499);
    if (over > 0) {
        cost_m += over * cost;
    }
    printf("%d\n", cost_m);
    scanf("%d", &number);
    switch (number) {
        case 0:
            printf("Ноль");
            break;
        case 1:
            printf("Один");
            break;
        case 2:
            printf("Два");
            break;
        case 3:
            printf("Три");
            break;
        case 4:
            printf("Четыре");
            break;
        case 5:
            printf("Пять");
            break;
        case 6:
            printf("Шесть");
            break;
        case 7:
            printf("Семь");
            break;
        case 8:
            printf("Восемь");
            break;
        case 9:
            printf("Девять");
            break;
    }
}


