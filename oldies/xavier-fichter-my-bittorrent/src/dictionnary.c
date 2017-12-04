/* Author: xavier.fichter */

#include "bittorrent.h"

/* Create a new dictionary */
struct dictionnary *dictionnary_init(char* key, struct b_type value)
{
  struct dictionnary *d = malloc(sizeof(struct dictionnary));
  d->key = key;
  d->value = value;
  d->next = NULL;
  return d;
}

/* Add an new entrie to a dictionary */
void dictionnary_add(struct dictionnary *d, char *key, struct b_type  value)
{
  if (!d->next)
  {
    d->next = dictionnary_init(key, value);
    return;
  }
  dictionnary_add(d->next, key, value);

}

/* Print a dictionary, JSON formatted */
static void dictionnary_print_rec(struct dictionnary *d, unsigned indent)
{
  if (!d)
    return;
  for(unsigned i = 0 ; i < indent ; i++)
    printf(" ");
  if(d->value.type == STRING)
  {
    printf("\"%s\": \"", d->key);
    mystr_print(d->value.value.string);
    printf("\"");
    if(d->next)
      printf(",\n");
    else
      printf("\n");
  }
  else if(d->value.type == INTEGER)
  {
    printf("\"%s\": %d", d->key, d->value.value.integer);
    if(d->next)
      printf(",\n");
    else
      printf("\n");
  }
  else if (d->value.type == LIST)
  {
    printf("\"%s\": ", d->key);
    list_print(d->value.value.list);
    if(d->next)
      printf(",\n");
    else
      printf("\n");
  }
  else if (d->value.type == DICTIONNARY)
  {
    printf("\"%s\": ", d->key);
    dictionnary_print(d->value.value.dictionnary, indent);
    if(d->next)
      printf(",\n");
    else
      printf("\n");
  }
  dictionnary_print_rec(d->next, indent);
}


void dictionnary_print(struct dictionnary *d, unsigned indent)
{
  if (!d)
    return;
  for(unsigned i = 0 ; i < indent ; i++)
    printf(" ");
  printf("{\n");
  dictionnary_print_rec(d, indent + 4);
  for(unsigned i = 0 ; i < indent ; i++)
    printf(" ");
  printf("}\n");
}

/* Free a dictionary */
void dictionnary_free(struct dictionnary *d)
{
  free(d->key);
  if(d->next)
    dictionnary_free(d->next);
  free(d);
}
