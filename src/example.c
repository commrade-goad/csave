#include <stdlib.h>
#include <stdio.h>
#include "type.h"

void encode_string(struct Data *data) {
    for (int i = 0; i < data->len; i++) {
        for (int j = 0; j < data->arr[i].len - 1; j++) {
            data->arr[i].str[j] += 13;
        }
    }
}

void decode_string(struct Data *data) {
    for (int i = 0; i < data->len; i++) {
        for (int j = 0; j < data->arr[i].len - 1; j++) {
            data->arr[i].str[j] -= 13;
        }
    }
}

FILE *load_file(char *path, char *mode) {
    FILE *file = fopen(path, mode);
    if (file == NULL) {
        perror("Error opening file");
        // file = NULL;
        exit(1);
    }
    return file;
}

int write_file(char *path, struct Data data) {
    FILE *file = load_file(path, "wb");
    encode_string(&data);

    fwrite(&data.len, sizeof(int), 1, file);
    for(int i = 0; i < data.len; i++) {
        fwrite(&data.arr[i].len, sizeof(int), 1, file);
        fwrite(data.arr[i].str, sizeof(char), data.arr[i].len, file);
    }
    fclose(file);
    return 1;
}

int read_file(char *path, struct Data *data) {
    FILE *file = load_file(path, "rb");

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
    decode_string(data);

    fclose(file);
    return 1;
}
