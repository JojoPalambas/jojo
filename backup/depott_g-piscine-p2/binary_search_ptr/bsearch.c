/* bsearch.c */
#include <stdio.h>
#include <stdlib.h>

int *binary_search(int *begin, int *end, int elt)
{
  int *mid = begin + (end - begin) / 2;
  if (*mid == elt)
    return mid;
  if (end - begin <= 1)
    return begin;

  if (elt < *mid)
    return binary_search(begin, mid, elt);
  return binary_search(mid, end, elt);
}
