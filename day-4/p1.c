#include <stdio.h>

int get_pair(int *a1, int *a2, int *b1, int *b2);
int contains(int  a1, int  a2, int  b1, int  b2);

int main()
{
  int a1, a2, b1, b2;
  int contained = 0;
  while (get_pair(&a1, &a2, &b1, &b2)) {
    contained += contains(a1, a2, b1, b2);
  }
  printf("%d\n", contained);
}
