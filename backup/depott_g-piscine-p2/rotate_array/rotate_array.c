/* rotate_array.c */
#include <stdio.h>
#include <stdlib.h>

int rotate(int *array, int size, int k)
{
  if (array == NULL || size <= 0)
    return 0;

  k %= size;

  int *save = malloc(sizeof (int) * size);
  for (int i = 0; i < size; i++)
    save[i] = array[(i + k) % size];
  for (int i = 0; i < size; i++)
    array[i] = save[i];
  free(save);

  return 1;
}
