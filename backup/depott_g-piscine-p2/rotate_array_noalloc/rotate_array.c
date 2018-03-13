/* rotate_array.c */
#include <stdio.h>
#include <stdlib.h>

int rotate(int *array, int size, int k)
{
  if (array == NULL || size <= 0)
    return 0;

  k %= size;

  int start = 0;
  int count = 0;
  int cur = array[0];
  int cur_pos = 0;

  while (count < size)
  {
    cur_pos += k;
    cur_pos %= size;

    int tmp = array[cur_pos];
    array[cur_pos] = cur;
    cur = swp;

    n++;
  }

  return 1;
}

int main()
{
  int *array = malloc(sizeof (int) * 5);
  for (int i = 0;  i < 5; i++)
    array[i] = i;

  rotate(array, 5, 3);
  for (int i = 0; i < 5; i++)
    printf("%d ", array[i]);
  printf("\n");

  return 0;
}

