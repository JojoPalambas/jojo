#include <stdio.h>


void rot_x(char* s, int x)
{
  if (!s)
    return;

  int i = 0;
  while (s[i] != '\0')
  {
    if (s[i] >= 'A' && s[i] <= 'Z')
    {
      printf("%d ", s[i]);
      s[i] += x;
      printf("%d ", s[i]);
      while (s[i] > 'Z')
        s[i] -= 26;
      while (s[i] < 'A')
        s[i] += 26;
      printf("%c\n", s[i]);
    }
    else if (s[i] >= 'a' && s[i] <= 'z')
    {
      printf("%d ", s[i]);
      s[i] += x;
      printf("%d ", s[i]);
      while (s[i] > 'z')
        s[i] -= 26;
      while (s[i] < 'a')
        s[i] += 26;
      printf("%c\n", s[i]);
    }
    i++;
  }
  return;
}
