#include <limits.h>
#include <stdio.h>
#include "util.h"

void printb(unsigned int v) {
  unsigned int mask = (int)1 << (sizeof(v) * CHAR_BIT - 1);
  int count = 0;
  do {
      putchar(mask & v ? '1' : '0');
      count++;
      if (count == 8 || count == 16 || count == 24)
          printf("_");
  } while (mask >>= 1);
  printf("\n");
}
