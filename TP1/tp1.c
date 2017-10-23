#include <stdio.h>
#include <math.h>

unsigned int_width(int i)
{
    int x = 0;
    int cpi = i;
    while (cpi != 0)
    {
        cpi /= 10;
        x++;
    }
    if (i == 0)
        return 1;
    if (i < 0)
        return x + 1;
    return x;
}

unsigned ints_width(const int* tab, unsigned count)
{
    unsigned widest = 0;
    unsigned cur = 0;
    for (unsigned i = 0; i < count; i++)
    {
        cur = int_width(tab[i]);
        if (cur > widest)
            widest = cur;
    }
    return widest;
}

void print_int_array(FILE* out, const int* tab, unsigned count)
{
    unsigned int_size = ints_width(tab, count) + 1;
    unsigned index_size = int_width(count - 1);

    // Current size of the line
    int cur_line = 0;
    for (unsigned i = 0; i < count; i++)
    {
        // If end of line
        if (cur_line + int_size > 80)
        {
            fprintf(out, "\n");
            cur_line = 0;
        }
        // If beginning of line
        if (cur_line == 0)
        {
            fprintf(out, "%*s", index_size - int_width(i), "");
            fprintf(out, "[%u]", i);
            cur_line = index_size + 2;
        }
        fprintf(out, "%*d", int_size, tab[i]);
        cur_line += int_size;
    }
    fprintf(out, "\n");
}



int main(void)
{
    int a[] = 
    {
        1, 2, 3, 4, 5, 6, 13, -35, 129, -4, 123, -4555, 1341, 2432, 111, 0, 1230
    };

    unsigned asize = sizeof(a)/sizeof(*a);
    puts("before");
    print_int_array(stdout, a, asize);
    insert_sort(a, asize);
    puts("after");

    return 0;
}
