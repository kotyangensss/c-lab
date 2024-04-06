#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *f;
    f = fopen(argv[argc-1], "r");
    char *s;
    int n = 0;
    while (feof(f)==0) {
        n++;
        fgets(s, 256, f);
        if (n % 2 == 0){
            fprintf(stdout, s);
        }
    }
    fclose(f);
    return 0;
}
