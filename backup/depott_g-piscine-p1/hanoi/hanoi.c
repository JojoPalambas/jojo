#include <stdio.h>

void hanoi_rec(unsigned n, int src, int dst, int mid)
{
  if (n == 1)
    printf("%d->%d\n", src, dst);
  else
  {
    hanoi_rec(n - 1, src, mid, dst);
    printf("%d->%d\n", src, dst);
    hanoi_rec(n - 1, mid, dst, src);
  }
}

void hanoi(unsigned n)
{
  hanoi_rec(n, 1, 2, 3);
}
