#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "example.c"

void encode_string(struct Data *data);
void decode_string(struct Data *data);
FILE *load_file(char *path, char *mode);
int write_file(char *path, struct Data data);
int read_file(char *path, struct Data *data);

#endif // !EXAMPLE_H
