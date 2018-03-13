#include <stdio.h>

int find_max(char histo[], int size)
{
  int max = 0;
  int index = -1;
  
  for (int i = 0; i < size; i++)
  {
    if (histo[i] > max)
    {
      max = histo[i];
      index = i;
    }
  }
  
  if (index > 0)
    histo[index] = 0;
  return index;
}

void freq_analysis(const char text[], const char table[])
{
  char histo[26] =
  {
    0
  };

  int i = 0;
  while (text[i] != '\0' && table[0] != '\0')
  {
    histo[text[i] - 65]++;
    i++;
  }

  int max_index = -2;
  i = 0;
  while (max_index != -1)
  {
    max_index = find_max(histo, 26);
    if (max_index != -1)
      printf("%c %c\n", max_index + 65, table[i]);
    i++;
  }
}
