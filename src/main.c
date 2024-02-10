#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"

#define PATH "./data.bin"

int write_file(char *path, struct Data data) {
    FILE *file = fopen(path, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    fwrite(&data.len, sizeof(int), 1, file);
    for(int i = 0; i < data.len; i++) {
        fwrite(&data.arr[i].len, sizeof(int), 1, file);
        fwrite(data.arr[i].str, sizeof(char), data.arr[i].len, file);
    }
    fclose(file);
    return 1;
}

int read_file(char *path, struct Data *data) {
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    fread(&data->len, sizeof(int), 1, file);
    data->arr = malloc(sizeof(struct String) * data->len);

    for(int i = 0; i < data->len; i++) {
        fread(&data->arr[i].len, sizeof(int), 1, file);
        int str_len = data->arr[i].len;
        data->arr[i].str = malloc(sizeof(char) * str_len);
        for(int j = 0; j < str_len; j++) {
            fread(&data->arr[i].str[j], sizeof(char), 1, file);
        }
    }

    fclose(file);
    return 1;
}

int main (int argc, char** argv) {

    if (argc < 2) {
        perror("ERR: Not enought args.");
        return 1;
    }

    if (!strcmp(argv[1], "read")) {
        struct Data result;
        read_file(PATH, &result);
        for(int i = 0; i < result.len; i++) {
            printf("[%d] : %s\n", i, result.arr[i].str);
            free(result.arr[i].str);
        }
        free(result.arr);
    }
    if (!strcmp(argv[1], "write")) {
        int n = 1;
        char something[1024];
        int tracker = 0;
        struct Data testi;
        testi.len = n;
        testi.arr = malloc(sizeof(struct String) * testi.len);
        printf("HELP -> e(exit), a(add)\n");
        printf("=========================\n");
        while (tracker < 1) {
            char mode;
            printf("mode : ");
            scanf(" %c", &mode);
            if (mode == 'e') {
                if (n - 1 >= 1) {
                    write_file(PATH, testi);
                    for (int i = 0; i < testi.len; i++) {
                        free(testi.arr[i].str);
                    }
                    free(testi.arr);
                }
                tracker = 1;

            } else if (mode == 'a') {
                printf(" add : ");
                scanf(" %[^\n]*c", something);
                testi.len = n;
                testi.arr = realloc(testi.arr, sizeof(struct String) * testi.len);
                testi.arr[n-1].len = strlen(something);
                testi.arr[n-1].str = malloc(strlen(something));
                strncpy(testi.arr[n-1].str, something, strlen(something));
                n++;

            } else {
                continue;
            }
        }
    }
    return 0;
}
