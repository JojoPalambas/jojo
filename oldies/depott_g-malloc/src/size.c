#include "include.h"

static unsigned size;

/* Function that returns the size of a page */
unsigned page_size()
{
    if (!size)
        size = sysconf(_SC_PAGESIZE);
    return size;
}
