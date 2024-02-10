#ifndef TYPE_H
#define TYPE_H

struct String {
    int len;
    char *str;
};

struct Data {
    int len;
    struct String* arr;
};

#endif // !TYPE_H
