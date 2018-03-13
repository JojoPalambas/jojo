#include <stdio.h>

size_t my_strlen(const char* s)
{
  size_t i = 0;

  while (*s != '\0')
  {
    i++;
    s++;
  }

  return i;
}
