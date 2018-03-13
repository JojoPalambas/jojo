#ifndef LLIST_H
#define LLIST_H

#include "structures.h"

/* Initializes a new llist structure containing data */
struct llist *llist_init(void *data);

/* 
** Pushes data in a new llist structure linked at the end of ll.
** If ll is NULL, returns the result of llist_init(data).
*/
struct llist *llist_push(struct llist *ll, void *data);

/* Frees the entire llist structure given as argument, but not its data */
void llist_free(struct llist *ll);

/* 
** Applies the function given as argument to all the data of ll.
** Can be useful to print all the elements of the llist, or to free them.
*/
void llist_apply(struct llist *ll, void (*func)(void *data));

#endif
