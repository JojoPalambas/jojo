/* Author: xavier.fichter */

#include "bittorrent.h"

/* Return the length of str */

size_t mystrlen(char *str)
{
  if (!str)
    return 0;
  size_t len = 0;
  while(str[len])
    len++;
  return len;
}

/* Return 1 if a and b match, 0 otherwise */

int mystrcmp(char *a, char *b)
{
  if(mystrlen(a) != mystrlen(b))
    return 0;
  for(size_t i = 0 ; i < mystrlen(a) ; i++)
  {
    if(a[i] != b[i])
      return 0;
  }
  return 1;
}

/* Return 1 if str match one element of tab */

int mystr_in(char **tab, size_t len, char *str)
{
  for(size_t i = 0 ; i < len ; i++)
  {
    if(mystrcmp(str, tab[i]))
      return 1;
  }
  return 0;
}


void mystr_print(char *str)
{
  for (size_t i = 0 ; i < mystrlen(str) ; i++)
  {
    if (str[i] == '"')
      printf("\\%c", str[i]);
    else if (str[i] >= 32 && str[i] <= 126)
      printf("%c", str[i]);
    else
      printf("\\u00%02x", (str[i] & 0xff));
  }
}

char *concatx(char *s1, size_t *size1, const char *s2, size_t size2)
{
    s1 = realloc(s1, *size1 + size2);
    for (size_t i = 0; i < size2; i++)
        s1[*size1 + i] = s2[i];
    *size1 = *size1 + size2;
    return s1;
}
