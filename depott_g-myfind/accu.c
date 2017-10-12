#include "accu.h"

struct accumulator *accu_init(const char *path)
{
    struct accumulator *accu = malloc(sizeof (struct accumulator));
    if (!accu)
        return NULL;
    accu->pos = 0;
    if (path[0])
        accu_concat(accu, path);
    else
        accu_concat(accu, ".");
    return accu;
}

void accu_concat(struct accumulator *accu, const char *path)
{
    int i = 0;
    for (; path[i] && i + accu->pos < 4096; i++)
        accu->path[accu->pos + i] = path[i];
    accu->pos += i;
    accu->path[accu->pos] = 0;
}

void accu_print(struct accumulator *accu)
{
    printf("%s\n", accu->path);
}

void accu_print_concat(struct accumulator *accu, const char *path)
{
    printf("%s/%s\n", accu->path, path);
}
