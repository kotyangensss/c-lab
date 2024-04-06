#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    int len1 = 1, len2 = 1;
    scanf("%d", &n);
    char *s1, *s2, *copy_s1;
    s1 = (char *) malloc(len1 + n);
    scanf("%s", s1);
    while (s1[len1 - 1] != '\0') {
        ++len1;
    }
    s2 = (char *) malloc(len2 + n);
    scanf("%s", s2);
    while (s2[len2 - 1] != '\0') {
        ++len2;
    }
    copy_s1 = (char *) malloc(len1 + n);
    for (int i = 0; i < len1; ++i) {
        copy_s1[i] = s1[i];
        copy_s1[i + 1] = '\0';
    }
    for (int i = len1 - 1; i < len1 + n - 1; ++i) {
        copy_s1[i] = s2[i - len1 + 1];
        copy_s1[i + 1] = '\0';
    }
    printf("%s\n", copy_s1);
    for (int i = 0; i < n; ++i) {
        if (s1[i] != s2[i]) {
            printf("Не совпадают\n");
            break;
        }
        if (i == n - 1) {
            printf("Совпадают\n");
        }
    }
    for (int i = 0; i < len1; ++i) {
        copy_s1[i] = s1[i];
        copy_s1[i + 1] = '\0';
    }
    for (int i = 0; i < n; ++i) {
        copy_s1[i] = s2[i];
    }
    printf("%s\n", copy_s1);
    char ch;
    scanf("%s", &ch);
    int j = 0;
    while ((s1[j] != ch) && (s1[j] != '\0')) {
        ++j;
    }
    if (j < len1 - 1) {
        printf("%d\n", j + 1);
    } else {
        printf("Нет такого символа\n");
    }
    for (int i = 0; i < len2-1; ++i) {
        j = 0;
        putchar(s2[i]);
        while ((s1[j] != s2[i]) && (s1[j] != '\0')) {
            ++j;
        }
        if (j < len1 - 1) {
            printf(" - %d\n", j + 1);
        } else {
            printf(" - Нет такого символа\n");
        }

    }

}


