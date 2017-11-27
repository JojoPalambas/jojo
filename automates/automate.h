#include <stdio.h>
#include <stdlib.h>
#include <err.h>

struct link
{
    struct automate *dst;
    char name;
}

struct automate
{
    char name;

    int nb_links;
    struct link *links[2048];
}

struct automate *autom_init(char name);
void autom_add_lk(struct automate *autom, struct link *lk);
void free_all(void);
