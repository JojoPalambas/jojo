#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

int main(void)
{
    void **small_tests = malloc(1024 * sizeof (void*));
    for (int i = 0; i < 1024; i++)
    {
        //warnx("Small test %d being done", i);
        small_tests[i] = malloc(i);
    }
    write(1, "Small tests done\n", 17);

    void **big_tests = malloc(1024 * sizeof (void*));
    for (int i = 0; i < 1024; i++)
    {
        //warnx("Big test %d being done", i);
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
}
