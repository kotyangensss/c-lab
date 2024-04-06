#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#pragma pack(push, 1)
struct BmpHeader {
    unsigned char b1, b2;
    unsigned int size;
    unsigned short notUse1;
    unsigned short notUse2;
    unsigned int massPos;

    unsigned int headerLength;
    unsigned int width;
    unsigned int height;
    unsigned short colorPlaneNumber;
    unsigned short bitPixel;
    unsigned int compressMethod;
    unsigned int massLength;
    unsigned int massWidth;
    unsigned int massHeight;
    unsigned int colorNumber;
    unsigned int generalColorNumber;
};
struct BmpHeader bmp;
int time = 0;

void readmeta(FILE *file) {
    bmp.b1 = fgetc(file);
    bmp.b2 = fgetc(file);
    fread(&bmp.size, 4, 1, file);
    fread(&bmp.notUse1, 2, 1, file);
    fread(&bmp.notUse2, 2, 1, file);
    fread(&bmp.massPos, 4, 1, file);
    fread(&bmp.headerLength, 4, 1, file);
    fread(&bmp.width, 4, 1, file);
    fread(&bmp.height, 4, 1, file);
    fread(&bmp.colorPlaneNumber, 2, 1, file);
    fread(&bmp.bitPixel, 2, 1, file);
    fread(&bmp.compressMethod, 4, 1, file);
    fread(&bmp.massLength, 4, 1, file);
    fread(&bmp.massWidth, 4, 1, file);
    fread(&bmp.massHeight, 4, 1, file);
    fread(&bmp.colorNumber, 4, 1, file);
    fread(&bmp.generalColorNumber, 4, 1, file);
}

void writemeta(FILE *file) {
    fwrite(&bmp.b1, 1, 1, file);
    fwrite(&bmp.b2, 1, 1, file);
    fwrite(&bmp.size, 4, 1, file);
    fwrite(&bmp.notUse1, 2, 1, file);
    fwrite(&bmp.notUse2, 2, 1, file);
    fwrite(&bmp.massPos, 4, 1, file);
    fwrite(&bmp.headerLength, 4, 1, file);
    fwrite(&bmp.width, 4, 1, file);
    fwrite(&bmp.height, 4, 1, file);
    fwrite(&bmp.colorPlaneNumber, 2, 1, file);
    fwrite(&bmp.bitPixel, 2, 1, file);
    fwrite(&bmp.compressMethod, 4, 1, file);
    fwrite(&bmp.massLength, 4, 1, file);
    fwrite(&bmp.massWidth, 4, 1, file);
    fwrite(&bmp.massHeight, 4, 1, file);
    fwrite(&bmp.colorNumber, 4, 1, file);
    fwrite(&bmp.generalColorNumber, 4, 1, file);
}

unsigned char choose_bit(int x) {
    switch (x) {
        case 0:
            return 128;
        case 1:
            return 64;
        case 2:
            return 32;
        case 3:
            return 16;
        case 4:
            return 8;
        case 5:
            return 4;
        case 6:
            return 2;
        case 7:
            return 1;
    }
    return 0;
}

int num_of_neighbours(int x, int y, unsigned char img[][bmp.width]) {
    int counter = 0;
    if (y + 1 < bmp.height) {
        if ((img[y + 1][x / 8] & choose_bit(x % 8)) != 0) {
            counter++;
        }
    } else {
        if ((img[0][x / 8] & choose_bit(x % 8)) != 0) {
            counter++;
        }
    }
    if (y > 0) {
        if ((img[y - 1][x / 8] & choose_bit(x % 8)) != 0) {
            counter++;
        }
    } else {
        if ((img[bmp.height - 1][x / 8] & choose_bit(x % 8)) != 0) {
            counter++;
        }
    }
    if (x > 0) {
        if ((img[y][(x - 1) / 8] & choose_bit((x - 1) % 8)) != 0) {
            counter++;
        }
    } else {
        if ((img[y][(bmp.width - 1) / 8] & choose_bit((bmp.width - 1) % 8)) != 0) {
            counter++;
        }
    }
    if (x + 1 < bmp.width) {
        if ((img[y][(x + 1) / 8] & choose_bit((x + 1) % 8)) != 0) {
            counter++;
        }
    } else {
        if ((img[y][0] & choose_bit(0 % 8)) != 0) {
            counter++;
        }
    }

    if (y + 1 < bmp.height) {
        if (x + 1 < bmp.width) {
            if ((img[y + 1][(x + 1) / 8] & choose_bit((x + 1) % 8)) != 0) {
                counter++;
            }
        } else {
            if ((img[y + 1][0] & choose_bit(0 % 8)) != 0) {
                counter++;
            }
        }
        if (x > 0) {
            if ((img[y + 1][(x - 1) / 8] & choose_bit((x - 1) % 8)) != 0) {
                counter++;
            }
        } else {
            if ((img[y + 1][(bmp.width - 1) / 8] & choose_bit((bmp.width - 1) % 8)) != 0) {
                counter++;
            }
        }
    } else {
        if (x + 1 < bmp.width) {
            if ((img[0][(x + 1) / 8] & choose_bit((x + 1) % 8)) != 0) {
                counter++;
            }
        } else {
            if ((img[0][0] & choose_bit(0 % 8)) != 0) {
                counter++;
            }
        }
        if (x > 0) {
            if ((img[0][(x - 1) / 8] & choose_bit((x - 1) % 8)) != 0) {
                counter++;
            }
        } else {
            if ((img[0][(bmp.width - 1) / 8] & choose_bit((bmp.width - 1) % 8)) != 0) {
                counter++;
            }
        }
    }

    if (y > 0) {
        if (x + 1 < bmp.width) {
            if ((img[y - 1][(x + 1) / 8] & choose_bit((x + 1) % 8)) != 0) {
                counter++;
            }
        } else {
            if ((img[y - 1][0 / 8] & choose_bit(0 % 8)) != 0) {
                counter++;
            }
        }
        if (x > 0) {
            if ((img[y - 1][(x - 1) / 8] & choose_bit((x - 1) % 8)) != 0) {
                counter++;
            }
        } else {
            if ((img[y - 1][(bmp.width - 1) / 8] & choose_bit((bmp.width - 1) % 8)) != 0) {
                counter++;
            }
        }
    } else {
        if (x + 1 < bmp.width) {
            if ((img[bmp.height - 1][(x + 1) / 8] & choose_bit((x + 1) % 8)) != 0) {
                counter++;
            }
        } else {
            if ((img[bmp.height - 1][0] & choose_bit(0 % 8)) != 0) {
                counter++;
            }
        }
        if (x > 0) {
            if ((img[bmp.height - 1][(x - 1) / 8] & choose_bit((x - 1) % 8)) != 0) {
                counter++;
            }
        } else {
            if ((img[bmp.height - 1][(bmp.width - 1) / 8] & choose_bit((bmp.width - 1) % 8)) != 0) {
                counter++;
            }
        }
    }
    return counter;
}

void kill(int x, int y, unsigned char img[][bmp.width], unsigned char new[][bmp.width]) {
    int bit = x % 8;
    x = x / 8;
    if ((img[y][x] & choose_bit(bit)) != 0) {
        new[y][x] -= choose_bit(bit);
    }

}

void revive(int x, int y, unsigned char img[][bmp.width], unsigned char new[][bmp.width]) {
    int bit = x % 8;
    x = x / 8;
    if ((img[y][x] & choose_bit(bit)) == 0) {
        new[y][x] += choose_bit(bit);
    }
}

void change(unsigned char prev[][bmp.width], unsigned char new[][bmp.width]) {
    for (int y = 0; y < bmp.height; y++) {
        for (int x = 0; x < bmp.width; x++) {
            int num = num_of_neighbours(x, y, prev);
            if (num == 3) {
                revive(x, y, prev, new);
            } else if (num == 2) {

            } else {
                kill(x, y, prev, new);
            }
        }
    }
    time++;
}

int save(unsigned char prev[][bmp.width], unsigned char new[][bmp.width], FILE *file) {
    int change = 0;
    int alive = 0;
    for (int i = 0; i < bmp.height; i++) {
        for (int j = 0; j < (bmp.width / 32 + ((bmp.width % 32) == 0 ? 0 : 1)) * 4; j++) {
            fwrite(&new[i][j], sizeof(new[i][j]), 1, file);
            if (new[i][j] != prev[i][j]) {
                change++;
            }
            if (new[i][j] != 0) {
                alive++;
            }
        }
    }
    if (change == 0) {
        return change;
    }
    return alive;
}

void upd_name(char name[]) {
    int copy = time;
    while (copy > 0) {
        char ch[10];
        ch[0] = (copy % 10) + 48;
        ch[1] = '\0';
        strcat(ch, name);
        for (int i = 0; i < strlen(ch); i++) {
            name[i] = ch[i];
        }
        copy /= 10;
    }
}

int main(int argc, char *argv[]) {
    char name[10];
    FILE *f;
    f = fopen(argv[2], "rb");
    if (f == NULL) {
        return -1;
    }
    readmeta(f);
    unsigned char buf[bmp.massPos - 54];
    fread(&buf, sizeof(buf), 1, f);
    unsigned char prev[bmp.height][bmp.width];
    unsigned char new[bmp.height][bmp.width];
    for (int i = 0; i < bmp.height; i++) {
        for (int j = 0; j < (bmp.width / 32 + ((bmp.width % 32) == 0 ? 0 : 1)) * 4; j++) {
            fread(&prev[i][j], sizeof(unsigned char), 1, f);
            new[i][j] = prev[i][j];
        }
    }
    int period = 1;
    int max_time = 100;
    fclose(f);
    if (argc > 5) {
        if (strstr(argv[5], "--dump_freq") != NULL) {
            period = atoi(argv[6]);
        } else if (strstr(argv[5], "--max_iter") != NULL) {
            max_time = atoi(argv[6]);
        }
        if (argc > 7) {
            if (strstr(argv[7], "--dump_freq") != NULL) {
                period = atoi(argv[8]);
            } else if (strstr(argv[7], "--max_iter") != NULL) {
                max_time = atoi(argv[8]);
            }
        }
    }
    for (int i = 0; i < max_time; i++) {
        change(prev, new);
        if (time % period == 0) {
            upd_name(name);

            FILE *file;
            char *result = malloc(strlen(argv[4]) + 10 + 1);
            strcpy(result, argv[4]);
            strcat(result, "\\");
            strcat(result, name);
            strcat(result, ".bmp");
            file = fopen(result, "wb");
            free(result);
            if (file == NULL) {
                return 0;
            }

            writemeta(file);
            fwrite(&buf, sizeof(buf), 1, f);


            if (save(prev, new, file) == 0) {
                break;
            }

            for (int i = 0; i < 10; i++) {
                name[i] = '\0';
            }
            fclose(file);
        }
        for (int i = 0; i < bmp.height; i++) {
            for (int j = 0; j < (bmp.width / 32 + ((bmp.width % 32) == 0 ? 0 : 1)) * 4; j++) {
                prev[i][j] = new[i][j];
            }
        }
    }
    return 0;
}
