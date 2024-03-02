#include <string.h>
#include "type.h"
#include "example.h"

#define BUFF_SIZE 1024
#define PATH "./data.bin"

void write_dialog(struct Data *testi, int is_alloc) {
    int n;
    if (is_alloc == 1) {
        n = testi->len;
    } else {
        n = 0;
    }
    char something[BUFF_SIZE];
    int tracker = 0;
    testi->len = n;
    if (is_alloc != 1) {
        testi->arr = malloc(sizeof(struct String) * testi->len);
    } else {
        testi->arr = realloc(testi->arr, sizeof(struct String) * testi->len);
    }
    printf("HELP -> e(exit), a(add), p(print), d(delete)\n");
    printf("=========================\n");
    while (tracker < 1) {
        char mode;
        printf("mode : ");
        scanf(" %c", &mode);
        n = testi->len + 1;
        if (mode == 'e') {
            if (n - 1 >= 1) {
                write_file(PATH, *testi);
                for (int i = 0; i < testi->len; i++) {
                    free(testi->arr[i].str);
                }
                free(testi->arr);
            }
            tracker = 1;

        } else if (mode == 'a') {
            printf(" add : ");
            scanf(" %[^\n]*c", something);
            int len = strlen(something);
            testi->len = n;
            testi->arr = realloc(testi->arr, sizeof(struct String) * testi->len);
            testi->arr[n-1].len = len + 1;
            testi->arr[n-1].str = malloc(len * sizeof(char));
            strncpy(testi->arr[n-1].str, something, len);
            testi->arr[n-1].str[len] = '\0';
            n++;

        } else if (mode == 'p') {
            for(int i = 0; i < testi->len; i++) {
                printf("[%d] : %s\n", i, testi->arr[i].str);
            }
        } else if (mode == 'd') {
            int idx;
            for(int i = 0; i < testi->len; i++) {
                printf("[%d] : %s\n", i, testi->arr[i].str);
            }
            printf(" del : ");
            scanf("%d", &idx);
            if (idx != testi->len - 1) {
                for (int i = idx; i < testi->len - 1;i++) {
                    testi->arr[i] = testi->arr[i+1];
                }
            }
            testi->len -= 1;
            testi->arr = realloc(testi->arr, sizeof(struct String) * testi->len);
        } else {
            continue;
        }
    }
}

int main (int argc, char** argv) {

    if (argc < 2) {
        perror("ERR: Not enought args.");
        return 1;
    }

    if (!strncmp(argv[1], "read", strlen("read"))) {
        struct Data result;
        read_file(PATH, &result);
        for(int i = 0; i < result.len; i++) {
            printf("[%d] : %s\n", i, result.arr[i].str);
            free(result.arr[i].str);
        }
        free(result.arr);
    } else if (!strncmp(argv[1], "write", strlen("write"))) {
        struct Data result;
        write_dialog(&result, 0);
    } else if (!strncmp(argv[1], "rw", strlen("rw"))) {
        struct Data result;
        read_file(PATH, &result);
        write_dialog(&result, 1);
    }
    else {
        return 1;
    }
    return 0;
}
