#include <stdio.h>
#include <stdlib.h>

struct accumulator
{
    char path[4096];
    size_t pos;
};

struct accumulator *accu_init(const char *path);
void accu_concat(struct accumulator *accu, const char *path);
void accu_print(struct accumulator *accu);
void accu_print_concat(struct accumulator *accu, const char *path);
