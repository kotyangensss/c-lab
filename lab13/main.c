#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Id3v2 {
    char tag[4];
    char *title;
    char *album;
    char *artist;
    char *year;
    char *genre;
    char *track;
    char *comment;
};

struct Id3v2 s;
char buf[1024];
char tag1[5];
int counter = 0;

void skip_nul() {
    while ((int) buf[counter] == 0) {
        counter++;
    }
}

int upd_tag() {
    for (int i = 0; i < 4; i++) {
        tag1[i] = buf[counter];
        counter++;
    }
    tag1[4] = '\0';
    return counter - 3;
}

int upd_len() {
    return (int) buf[counter] - 1;
}

void find_title() {
    while (strcmp(tag1, "TIT2") != 0 && strcmp(tag1, "TT2") != 0) {
        counter = upd_tag();
    }
    counter += 3;
    skip_nul();
}


void find_album() {
    while (strcmp(tag1, "TALB") != 0 && strcmp(tag1, "TAL") != 0) {
        counter = upd_tag();
    }
    counter += 3;
    skip_nul();
}


void find_artist() {
    while (strcmp(tag1, "TPE1") != 0 && strcmp(tag1, "TP1") != 0) {
        counter = upd_tag();
    }
    counter += 3;
    skip_nul();
}


void find_year() {
    while (strcmp(tag1, "TYER") != 0 && strcmp(tag1, "TYE") != 0) {
        counter = upd_tag();
    }
    counter += 3;
    skip_nul();
}

void find_genre() {
    while (strcmp(tag1, "TCON") != 0 && strcmp(tag1, "TCO") != 0) {
        counter = upd_tag();
    }
    counter += 3;
    skip_nul();
}

void find_track() {
    while (strcmp(tag1, "TRCK") != 0 && strcmp(tag1, "TRK") != 0) {
        counter = upd_tag();
    }
    counter += 3;
    skip_nul();
}

void find_comment() {
    while (strcmp(tag1, "COMM") != 0 && strcmp(tag1, "COM") != 0) {
        counter = upd_tag();
    }
    counter += 3;
    skip_nul();
}

void create(FILE *f) {
    int len;
    for (int i = 0; i < 1024; i++) {
        buf[i] = fgetc(f);
    }


    for (int i = 0; i < sizeof(s.tag); i++) {
        s.tag[i] = buf[i];
    }
    s.tag[3] = '\0';


    find_title();
    len = upd_len();
    s.title = (char *) malloc(len * sizeof(char));
    counter++;
    skip_nul();
    for (int i = 0; i < len; i++) {
        s.title[i] = buf[counter];
        counter++;
    }
    s.title[len] = '\0';


    find_album();
    len = upd_len();
    s.album = (char *) malloc(len * sizeof(char));
    counter++;
    skip_nul();
    for (int i = 0; i < len; i++) {
        s.album[i] = buf[counter];
        counter++;
    }
    s.album[len] = '\0';


    find_artist();
    len = upd_len();
    s.artist = (char *) malloc(len * sizeof(char));
    counter++;
    skip_nul();
    for (int i = 0; i < len; i++) {
        s.artist[i] = buf[counter];
        counter++;
    }
    s.artist[len] = '\0';


    find_year();
    len = upd_len();
    s.year = (char *) malloc(len * sizeof(char));
    counter++;
    skip_nul();
    for (int i = 0; i < len; i++) {
        s.year[i] = buf[counter];
        counter++;
    }
    s.year[len] = '\0';


    find_genre();
    len = upd_len();
    s.genre = (char *) malloc(len * sizeof(char));
    counter++;
    skip_nul();
    for (int i = 0; i < len; i++) {
        s.genre[i] = buf[counter];
        counter++;
    }
    s.genre[len] = '\0';


    find_track();
    len = upd_len();
    s.track = (char *) malloc(len * sizeof(char));
    counter++;
    skip_nul();
    for (int i = 0; i < len; i++) {
        s.track[i] = buf[counter];
        counter++;
    }
    s.track[len] = '\0';
}

void free_struct() {
    free(s.title);
    free(s.album);
    free(s.artist);
    free(s.year);
    free(s.genre);
    free(s.track);
    free(s.comment);
}

void show() {
    printf("Title:    %s\n", s.title);
    printf("Album:    %s\n", s.album);
    printf("Artist:   %s\n", s.artist);
    printf("Year:     %s\n", s.year);
    printf("Genre:    %s\n", s.genre);
    printf("Track:    %s\n", s.track);
}

void change(FILE *f,char* st){
    int len = upd_len();
    counter++;
    skip_nul();
    fseek(f, counter, 0);
    for (int i = 0; i < strlen(st); i++) {
        fputc(st[i], f);
        counter++;
    }
    for (int i = 0; i < len - strlen(st); i++) {
        fputc(0, f);
    }
}

void choose(FILE *f, char *str, int key, char *st) {
    if (strstr(str, "TIT2") != NULL || strstr(str, "TT2") != NULL) {
        if (!key) {
            printf("Title: %s\n", s.title);
        } else {
            find_title();
        }
    } else if (strstr(str, "TALB") != NULL || strstr(str, "TAl") != NULL) {
        if (!key) {
            printf("Album: %s\n", s.album);
        } else {
            find_album();
        }
    } else if (strstr(str, "TPE1") != NULL || strstr(str, "TP1") != NULL) {
        if (!key) {
            printf("Artist: %s\n", s.artist);
        } else {
            find_artist();
        }
    } else if (strstr(str, "TYER") != NULL || strstr(str, "TYE") != NULL) {
        if (!key) {
            printf("Year: %s\n", s.year);
        } else {
            find_year();
        }
    } else if (strstr(str, "TCON") != NULL || strstr(str, "TCO") != NULL) {
        if (!key) {
            printf("Genre: %s\n", s.genre);
        } else {
            find_genre();
        }
    } else if (strstr(str, "TRCK") != NULL || strstr(str, "TRK") != NULL) {
        if (!key) {
            printf("Track: %s\n", s.track);
        } else {
            find_track();
        }
    } else if (strstr(str, "COMM") != NULL || strstr(str, "COM") != NULL) {
        if (!key) {
            printf("Comment: %s\n", s.comment);
        } else {
            find_comment();
        }
    }
    if (key){
        change(f,st);
    }
}


int main(int argc, char *argv[]) {
    char *song;
    song = (char *) malloc((strlen(argv[1]) - 11));
    for (int i = 11; i < strlen(argv[1]); i++) {
        song[i - 11] = argv[1][i];
    }
    song[strlen(argv[1]) - 11] = '\0';
    FILE *f;
    f = fopen(song, "r+");
    if (f == NULL) {
        return -1;
    }
    create(f);
    if (strcmp(argv[2], "--show") == 0) {
        show();
    } else if (strstr(argv[2], "--get") != NULL) {
        choose(f, argv[2], 0, "useless");
    } else if (strstr(argv[2], "--set") != NULL) {
        char *st;
        st = (char *) malloc((strlen(argv[3]) - 8) * sizeof(char));
        for (int i = 0; i < (strlen(argv[3]) - 8); i++) {
            st[i] = argv[3][i + 8];
        }
        counter = 0;
        tag1[0] = '0';
        choose(f, argv[2], 1, st);
        free(st);
    }
    free_struct();
    fclose(f);
    free(song);
    return 0;
}