#include <stdio.h>

int read_reverse(void)
{
  char s1[512] = "";
  char s2[512] = "";

  scanf("%s %s", s1, s2);

  int pos2 = 0;
  while (s2[pos2] != '\0')
    pos2++;
  pos2--;

  int pos1 = 0;
  int nequal = -1;
  while (nequal == -1)
  {
    if (s1[pos1] == '\0' && s2[pos2] == '\0')
    {
      nequal = 0;
    }
    else if (s1[pos1] == '\0' || s2[pos2] == '\0')
    {
      
      nequal = 1;
    }
    else if(s1[pos1] != s2[pos2])
    {
      nequal = 1;
    }
    pos1++;
    pos2--;
  }

  return nequal;
}
