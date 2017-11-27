#include "automate.h"

struct automate *autom_init(char name)
{
    struct automate *autom = malloc(sizeof (struct autom));
    if (!autom)
        err(1, "Cannot create automate");
    autom->name = name;
    autom->nb_links = 0;
    autom->links = malloc(2048 * sizeof (void*));
    if (!autom->links)
        err(1, "Cannot create links list for an automate");
    return autom;
}

void autom_add_lk(struct automate *a1, struct automate *a2, char linkname)
{
    if (a1->nb_links >= 2048)
        errx(1, "Max number of links reached");
    a1->links[a2->nb_links] = dst;
    a1->nb_links++;
}

void free_all(void);
