/* mat_det.c */

#include <stdio.h>
#include <stdlib.h>


int mat_det_rec(int *mat[], int n)
{
  if (n == 1)
  {
    return mat[0][0];
  }
  int ret = 0;
  int sign = 1;

  for (int x = 0; x < n; x++)
  {
    int *m[n - 1];
    for (int i = 0; i < n - 1; i++)
    {
      int i2 = i >= x ? i + 1 : i;
      m[i] = mat[i2] + 1;
    }

    if (sign)
    {
      ret += mat[x][0] * mat_det_rec(m, n - 1);
    }
    else
    {
      ret -= mat[x][0] * mat_det_rec(m, n - 1);
    }
    sign = 1 - sign;
  }
  return ret;
}

int mat_det(int mat[4][4])
{
  int *m[4];
  for (int i = 0; i < 4; i++)
    m[i] = mat[i];
  return mat_det_rec(m, 4);
}
