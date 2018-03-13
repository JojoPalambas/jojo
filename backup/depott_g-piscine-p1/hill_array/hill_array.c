#include <stdio.h>

int top_of_the_hill(int tab[], size_t len)
{
  int up = 1;
  int top = -1;
  for (unsigned i = 0; i < len; i++)
  {
    if (i == len - 1)
    {
      if(up == 1)
        top = i;
      break;
    }
    else if (up)
    {
      if (tab[i] > tab[i + 1])
      {
        up = 0;
        top = i;
      }
    }
    else
    {
      if (tab[i] < tab[i + 1])
      {
        top = -1;
        break;
      }
    }
  }
  return top;
}
