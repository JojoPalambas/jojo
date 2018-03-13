#include "rt.h"

struct llist *llist_init(void *data)
{
    struct llist *ret = malloc(sizeof (struct llist));
    if (!ret)
    {
        fprintf(stderr, "Memory can't be allocated for llist");
        exit(1);
    }
    ret->data = data;
    ret->next = NULL;

    return ret;
}

struct llist *llist_push(struct llist *ll, void *data)
{
    if (!ll)
    {
        struct llist *ret = llist_init(data);
        return ret;
    }
    ll->next = llist_push(ll->next, data);
    return ll;
}

void llist_free(struct llist *ll)
{
    if (!ll)
        return;
    llist_free(ll->next);
    free(ll);
}

void llist_apply(struct llist *ll, void (*func)(void *data))
{
    if (!ll)
        return;
    func(ll->data);
    llist_apply(ll->next, func);
}
