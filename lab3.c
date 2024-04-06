#include <stdio.h>

int main() {
    int num, num5;
    scanf("%d", &num);
    printf("%o\n", num);
    printf("%x\n", num);
    printf("%x\n", num << 2);
    printf("%x\n", ~num);
    scanf("%x", &num5);
    printf("%x",num5 | num);
}
