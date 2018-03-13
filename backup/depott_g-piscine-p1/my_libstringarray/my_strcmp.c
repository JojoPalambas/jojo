#include <stdio.h>

int my_strcmp(const char* s1, const char* s2)
{
  int i = 0;
  int sum1 = 0;
  while (s1[i] != '\0')
  {
    sum1 += s1[i];
    i++;
  }
  i = 0;
  int sum2 = 0;
  while (s2[i] != '\0')
  {
    sum2 += s2[i];
    i++;
  }

  return sum1 - sum2;
}
