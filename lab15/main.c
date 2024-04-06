#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *arc_name;

void create(int argc, char *argv[]) {
    FILE *arch = fopen(arc_name, "wb");
    FILE *f;
    unsigned long long int sizes[128];
    for (int i = 4; i < argc; i++) {
        f = fopen(argv[i], "rb");
        if (f == NULL) {
            continue;
        }
        fseek(f, 0, 2);
        sizes[i - 4] = ftell(f);
        fseek(f, 0, 0);
        fclose(f);
    }
    int numFiles = argc - 4;
    fputc(numFiles, arch);
    for (int i = 0; i < argc - 4; i++) {
        fprintf(arch, "%s: ", argv[i + 4]);
        fwrite(&sizes[i], sizeof(unsigned long long int), 1, arch);
        fputc('*', arch);
    }
    fputc('\n', arch);
    for (int i = 4; i < argc; i++) {
        f = fopen(argv[i], "rb");
        if (f == NULL) {
            continue;
        }
        unsigned char buf[sizes[i - 4]];
        fread(&buf, sizeof(buf), 1, f);
        fwrite(&buf, sizeof(buf), 1, arch);
        fclose(f);
    }
    fclose(arch);
}

void list() {
    FILE *arch = fopen(arc_name, "rb");
    char ch = fgetc(arch);
    printf("Список файлов:\n");
    while (ch != '\n') {
        ch = fgetc(arch);
        if (ch == ':') {
            fseek(arch, 9, 1);
        } else if (ch != '*') {
            printf("%c", ch);
        }
        if (ch == '*') {
            printf("\n");
        }
    }
    fclose(arch);
}

void extract() {
    FILE *arch = fopen(arc_name, "rb");
    unsigned long long int names = 1;
    unsigned long long int body = 0;
    char chr = 'a';
    while (chr != EOF) {
        chr = fgetc(arch);
        body++;
        if (chr == '\n')
            break;
    }
    fseek(arch, 0, 0);
    int num = (int) fgetc(arch);
    char name[128];
    unsigned long long int sizef;
    FILE *f;
    for (int i = 0; i < num; i++) {
        int counter = 0;
        chr = fgetc(arch);
        while (chr != ':') {
            name[counter] = chr;
            chr = fgetc(arch);
            counter++;
        }
        names += counter;
        names += 11;
        fgetc(arch);
        fread(&sizef, 8, 1, arch);
        name[counter] = '\0';
        f = fopen(name, "wb");
        if (f == NULL)
            break;
        fseek(arch, body, 0);
        body += sizef;
        unsigned char buf[sizef];
        fread(&buf, sizeof(buf), 1, arch);
        fwrite(&buf, sizeof(buf), 1, f);
        fseek(arch, names, 0);
        fclose(f);
    }
}

int main(int argc, char *argv[]) {
    arc_name = argv[2];
    if (strstr(argv[3], "--create") != NULL) {
        create(argc, argv);
    } else if (strstr(argv[3], "--extract") != NULL) {
        extract();
    } else if (strstr(argv[3], "--list") != NULL) {
        list();
    }
    return 0;
}
