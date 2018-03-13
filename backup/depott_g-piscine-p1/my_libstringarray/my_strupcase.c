#include <stdio.h>

void my_strupcase(char* src)
{
  size_t i = 0;

  while (src[i] != '\0')
  {
    if (src[i] >= 'a' && src[i] <= 'z')
      src[i] -= 32;
    i++;
  }

  return;
}
