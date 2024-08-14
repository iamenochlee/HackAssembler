#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void int_to_bin(int n, char *ptr, int start_index, int end_index)
{

  for (int i = end_index; n > 0 && i >= start_index; i--)
  {
    int bin = n % 2;

    ptr[i] = '0' + bin;

    n = n >> 1;
  }
}
