#include <stdio.h>


int binary_search(const int vec[], size_t size, int elt)
{
  int mid = size / 2;
  if (vec[mid] == elt)
    return mid;

  if (vec[size - 1] == elt)
    return size - 1;

  if (size <= 2 && elt != vec[0] && elt != vec[size - 1])
    return -1;

  if (vec[mid] > elt)
    return binary_search(vec, size / 2, elt);
  return mid + binary_search(vec + mid, size / 2, elt);
}
