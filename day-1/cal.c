#include <stdio.h>

int get_number_line(void);

/* Get sequence of numbers with highest sum */
int main()
{
  int i, n, max;
  max = -1;
  while ((i = get_number_line()) != -1)
    if (i != 0)
      n += i;
    else {
      if (n > max) 
	max = n;
      n = 0;
    }
  if (n > max)
    max = n;
  printf("%d\n", max);
  return 0;
}

 
