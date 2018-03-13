#include <stdio.h>

void array_occurrence(int tab[])
{
  int histo[100] =
  {
    0
  };

  for (int i = 0; i < 100; i++)
    histo[tab[i]]++;

  for (int i = 0; i < 100; i++)
    if (histo[i] > 0)
      printf("%d %d\n", i, histo[i]);
}
