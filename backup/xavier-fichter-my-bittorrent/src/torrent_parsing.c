/* Author: xavier.fichter */

#include "bittorrent.h"

/* Parse a b-encoded string */
static char *string_parsing(FILE *file, char c)
{
  size_t len = 0;
  while (c != ':')
  {
    len = len * 10 + (c - 48);
    c = fgetc(file);
  }
  char *str = calloc(len + 1, sizeof(char));
  for (size_t i = 0 ; i < len ; i++)

    str[i] = fgetc(file);
  return str;
}

/* Parse a b-encoded integer */
static int integer_parsing(FILE *file)
{
  char c = fgetc(file);
  int sign = 0;
  if(c == '-')
  {
    sign = -1;
    c = fgetc(file);
  }
  else
    sign = 1;
  int res = 0;
  while (c != 'e')
  {
    res = res * 10 + (c - 48);
     c = fgetc(file);
  }
  return sign * res;
}

/* Parse a b-encoded list */
struct list *list_parsing(FILE *file)
{
  struct list *list = NULL;
  char c = fgetc(file);
  while (c != 'e')
  {
    struct b_type data;
    if (c >= '0' && c <= '9')
    {
      data.type = STRING;
      data.value.string = string_parsing(file, c);
    }
    else if (c == 'i')
    {
      data.type = INTEGER;
      data.value.integer = integer_parsing(file);
    }
    else if (c == 'l')
    {
      data.type = LIST;
      data.value.list = list_parsing(file);
    }
    else if (c == 'd')
    {
      data.type = DICTIONNARY;
      data.value.dictionnary = dictionnary_parsing(file);
    }
    if (!list)
      list = list_init(data);
    else
      list_add(list, data);
    c = fgetc(file);
  }
  return list;
}

/* Parse a b-encoded dictionary */
struct dictionnary *dictionnary_parsing(FILE *file)
{
  struct dictionnary *dico = NULL;
  char c = fgetc(file);
  while (c != 'e')
  {
    char *key = string_parsing(file, c);
    c = fgetc(file);
    struct b_type value;
    if (c >= '0' && c <= '9')
    {
      value.type = STRING;
      value.value.string = string_parsing(file, c);
    }
    else if (c == 'i')
    {
      value.type = INTEGER;
      value.value.integer = integer_parsing(file);
    }
    else if (c == 'l')
    {
      value.type = LIST;
      value.value.list = list_parsing(file);
    }
    else if (c == 'd')
    {
      value.type = DICTIONNARY;
      value.value.dictionnary = dictionnary_parsing(file);
    }
    if (!dico)
      dico = dictionnary_init(key, value);
    else
      dictionnary_add(dico, key, value);
    c = fgetc(file);
  }
  return dico;
}

/* Parse a .torrent file, and put the result in a dictionnary */
struct dictionnary *torrent_parsing(char *pathname)
{
  FILE *file = fopen(pathname, "r");
  if (!file)
  {
    fprintf(stderr, "Cant open %s", pathname);
    return NULL;
  }
  int test = fgetc(file);
  if (test == EOF)
    return NULL;
  struct dictionnary *dico = dictionnary_parsing(file);
  fclose(file);
  return dico;
}

/* Get the info_hash from the tracker answer */
char *get_info_as_str(char *pathname)
{
  FILE *file = fopen(pathname, "r");
  if (!file)
  {
    fprintf(stderr, "Cant open %s", pathname);
    return NULL;
  }
  char *buf = NULL;
  char c = fgetc(file);
  do
  {
    c = fgetc(file);
    if (c == '4')
    {
      if ((c = fgetc(file)) == ':' && (c = fgetc(file)) == 'i' && (c =
        fgetc(file)) == 'n' && (c = fgetc(file)) == 'f' && (c = fgetc(file) ==
        'o'))
        break;
    }
  } while (c != EOF);
  c = fgetc(file);
  size_t len = 0;
  while (c != EOF)
  {
    buf = concatx(buf, &len, &c, 1);
    c = fgetc(file);
  }
  buf[mystrlen(buf) - 1] = 0;
  return buf;
}
