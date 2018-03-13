#include <stdio.h>


unsigned array_min(const int arr[], unsigned start, unsigned size)
{
  int min = start;
  start++;
  for (; start < size; start++)
    if (arr[start] < arr[min])
      min = start;
  return min;
}

void selection_sort(int arr[], unsigned size)
{
  for (unsigned start; start < size - 1; start++)
  {
    unsigned min = array_min(arr, start, size);
    int sw = arr[min];
    arr[min] = arr[start];
    arr[start] = sw;
  }
}
