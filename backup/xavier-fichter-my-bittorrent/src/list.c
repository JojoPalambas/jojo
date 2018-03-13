/* Author: xavier.fichter */

#include "bittorrent.h"

struct list *list_init(struct b_type data)
{
  struct list *l = malloc(sizeof(struct list));
  l->data = data;
  l->next = NULL;
  return l;
}

void list_add(struct list *l, struct b_type data)
{
  if (!l->next)
  {
    l->next = list_init(data);
    return;
  }
  list_add(l->next, data);
}

static void list_print_rec(struct list *l)
{
  if (!l)
    return;
  if (l->data.type == STRING)
  {
    printf("\"");
    mystr_print(l->data.value.string);
    printf("\"");
    if(l->next)
      printf(", ");
  }
  else if (l->data.type == INTEGER)
  {
    printf("%d", l->data.value.integer);
    printf(", ");
  }
  else if (l->data.type == LIST)
  {
    list_print(l->data.value.list);
    if(l->next)
      printf(", ");
  }

  else if (l->data.type == DICTIONNARY)
  {
    dictionnary_print(l->data.value.dictionnary, 0);
    if(l->next)
      printf(", ");
  }
  list_print_rec(l->next);
}


void list_print(struct list *l)
{
  if (!l)
    return;
  printf("[");
  list_print_rec(l);
  printf("]");
}

void list_free(struct list *l)
{
  if(l->next)
    list_free(l->next);
  free(l);
}
