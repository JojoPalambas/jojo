#include "include.h"

void *calloc(size_t number, size_t size)
{
    void *ret = malloc(number * size);
    ret = memset(ret, 0, number * size);
    return ret;
}
