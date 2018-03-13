#include <stdio.h>

int pine(unsigned n)
{
  if (n < 3)
    return 1;

  for (unsigned i = 0; i < n; i++)
  {
    for (unsigned j = 0; j < n - i - 1; j++)
      printf(" ");
    for (unsigned j = 0; j < i * 2 + 1; j++)
      printf("*");
    printf("\n");
  }
  
  for (unsigned i = 0; i < n / 2; i++)
  {
    for (unsigned j = 0; j < n - 1; j++)
      printf(" ");
    printf("*");
    for (unsigned j = 0; j < n - 1; j++)
      printf(" ");
    printf("\n");
  }

  return 0;
}
