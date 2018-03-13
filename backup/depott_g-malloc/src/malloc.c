#include "include.h"

struct global global = { 0, NULL };

/* Function that moves any pointer n bytes */
void *move(void *ptr, int n)
{
    char *ret = ptr;
    return ret + n;
}

/* Function that returns the difference in bytes between two vectors */
int diff(void *ptr1, void *ptr2)
{
    char *c1 = ptr1;
    char *c2 = ptr2;
    return c1 - c2;
}

/* Function that returns the log2 of the closest power of two superior to n */
static unsigned char mylog2(unsigned n)
{
    n += 8;
    unsigned char ret = 0;
    unsigned tmp = n;
    for (; tmp > 1; tmp /= 2)
        ret++;

    return ret;
}

/*
** Function that returns -1 if the data block is corrupted, 1 if it is a small
** data block and 0 if it is a big data block
*/
static int is_small(char *s)
{
    // If the data block is small
    if (!s[0])
    {
        // If the small data block is corrupted
        if (s[4] != 73
         || s[5] != 112
         || s[6] != 15
         || s[7] != 97)
            return -1;
        return 1;
    }

    // If the data lock is big
    if (s[0] == 1)
    {
        // If the big data block is corrupted
        if (s[6] != 15
         || s[7] != 97)
            return -1;
        return 0;
    }

    // If the data block is corrupted
    return -1;
}

/* Creates a new page meant to store small data blocks */
static void init_small(char *loc, size_t size,
                       unsigned char used, unsigned char is_left)
{
    loc[0] = 0;
    loc[1] = used;
    loc[2] = mylog2(size);
    loc[3] = is_left;
    loc[4] = 73;
    loc[5] = 112;
    loc[6] = 15;
    loc[7] = 97;
}

/* Creates a new page meant to store small data blocks */
static void *create_small()
{
    char *ret = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE,             
                        MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
    init_small(ret, PAGE_SIZE, 0, 1);

    return ret;
}

/* Creates a new page meant to store big data blocks */
static void *create_big(size_t size)
{
    unsigned char *ret = mmap(NULL, size, PROT_READ | PROT_WRITE,             
                              MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
    ret[0] = 1;
    ret[1] = 1;
    uint32_t *ret2 = move(ret, 2);
    *ret2 = size / PAGE_SIZE;
    ret[6] = 15;
    ret[7] = 97;

    return ret;
}

/* Returns the closest exponent of two minus eight that can contain size */
static size_t matching_size(size_t size)
{
    size_t ret = 8;
    while (ret < size)
        ret = (ret + 8) * 2 - 8;
    return ret;
}

/* Returns 2 to the power n */
size_t pow2(char n)
{
    size_t ret = 1;
    while (n)
    {
        ret *= 2;
        n--;
    }
    return ret;
}

/*
** Searches in the page where to get the right size
** size must be a power of 2 minus 8 !
*/
void *get_small(char *page, size_t size, unsigned pos)
{
    // warnx("get_small(%p, %zu, %u)", page, size, pos);
    // If the current block is out of the page
    if (pos >= PAGE_SIZE)
        return NULL;

    // Get the position of the current block and the capacity of the block
    char *cur = move(page, pos);
    size_t blk_size = pow2(cur[2]) - 8;

    // If the block is too small or occupied
    if (blk_size < size || cur[1])
    {
        return get_small(page, size, pos + 8 + blk_size);
    }

    // If the size of the block is OK and the block is free
    if (blk_size == size && !cur[1])
    {
        cur[1] = 1;
        return cur;
    }
    
    // If the block is too big
    size_t new_blk_size = (blk_size + 8) / 2 - 8;
    init_small(cur, new_blk_size, cur[1], 1);
    init_small(move(cur, new_blk_size + 8), new_blk_size, 0, 0);
    return get_small(page, size, pos);
    /*size_t new_size = (size + 8) / 2 - 8;
    init_small(move(cur, new_size + 8), new_size);
    cur[2] -= mylog2(new_size);
    return get_small(page, size, pos);*/
}

void *malloc(size_t size)
{
    if (size == 0)
        return NULL;
    size = matching_size(size);

    int need_small = size <= (PAGE_SIZE - 8);
    void *ret = NULL;

    // If this is the first call of malloc
    if (!global.nb_pages)
    {
        global.nb_pages = 1;
        global.meta = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE,
                           MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
        if (!global.meta)
            return NULL;
    }

    void **cur = global.meta;
    unsigned pos = 0;

    // Traverses all the pointers to pages in the metadata pages
    while (pos < PAGE_SIZE * global.nb_pages)
    {
        if (!*cur)
        {
            if (need_small)
            {
                *cur = create_small();
                void *tmp = get_small(*cur, size, 0);
                return move(tmp, 8);
            }
            else
            {
                *cur = create_big(size);
                //*cur[1] = 1;
                return move(*cur, 8);
            }
        }

        int page_small = is_small(*cur);
        // If the data block is small and the needed allocation is small
        if (page_small == 1 && need_small)
        {
            ret = get_small(*cur, size, 0);
            if (ret)
                return move(ret, 8);
        }


        cur = move(cur, 8);
        pos += 8;
    }
    // If the end of the metadata pages is reached
    return NULL;
}
/*
int main(void)
{
    void **small_tests = malloc(1024 * sizeof (void*));
    for (int i = 0; i < 1024; i++)
    {
        small_tests[i] = malloc(i);
    }
    write(1, "Small tests done\n", 17);

    void **big_tests = malloc(1024 * sizeof (void*));
    for (int i = 0; i < 1024; i++)
    {
        //warnx("Big test %d done", i);
        big_tests[i] = malloc(i + 8192);
    }
    write(1, "Big tests done\n", 15);

    for (int i = 0; i < 1024; i++)
    {
        free(small_tests[i]);
        free(big_tests[i]);
    }
    write(1, "Elements free done\n", 19);
    free(small_tests);
    free(big_tests);
    write(1, "Lists free done\n", 16);
    return 0;
}*/
