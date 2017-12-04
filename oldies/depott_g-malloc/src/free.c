#include "include.h"

void free(void *ptr)
{
    if (!ptr)
        return;

    char *cur = move(ptr, -8);
    if (cur[6] != 15 || cur[7] != 97)
        return;
    if (*cur)
    {
        uint32_t *nb_pages = move(cur, 2);
        munmap(cur, *nb_pages);
        return;
    }
    cur[1] = 0;
    memset(cur + 8, 0, pow2(cur[2]));
}
