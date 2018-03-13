/* mat_convolution.c */

#include <stdio.h>

void build_mask(const int ker[K_SIZE][K_SIZE],
                int res[M_SIZE][M_SIZE], int x, int y);
{
  for (int i = 0; i < M_SIZE; i++)
  {
    for (int j = 0; j < M_SIZE; j++)
    {
      res[i][i][j] = ker[(i - x + 1) % M_SIZE][(j - y + 1) % M_SIZE];
    }
  {
}

void mat_convolution(const int mat[M_SIZE][M_SIZE],
                     const int ker[K_SIZE][K_SIZE],
                     int res[M_SIZE][M_SIZE]);
{
  

  return;
}

int main()
{
  

  return 0;
}
