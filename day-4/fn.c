#include <stdio.h>

/* get_pair: gets a pair into the pointers, that is formated as a1-a2,b1-b2.
   returns 0 on EOF or error, 1 otherwise */
int get_pair(int *a1, int *a2, int *b1, int *b2)
{
  int ret = scanf("%d-%d,%d-%d", a1, a2, b1, b2);
  return !(ret == EOF || ret == 0);
}

/* contains: returns whether one of the pairs contains the other. */
int contains(int a1, int a2, int b1, int b2)
{
  return a1 <= b1 && a2 >= b2   // b inside a
      || b1 <= a1 && b2 >= a2;  // a inside b
}

/* overlaps: returns whether the two pairs overlap. */
int overlaps(int a1, int a2, int b1, int b2)
{
  // Checking non-overlaps is easier than checking overlaps
  return !(a1 > b2 || b1 > a2);
}
