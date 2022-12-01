#include <stdio.h>

int get_number_line(void);

/* gets the sum of the three highest-sum integer sequences */
int main()
{
  int i, n, first, second, third;
  first = second = third = -1;
  while ((i = get_number_line()) != -1)
    if (i != 0)
      n += i;
    else {
      if (n > first) {
	third = second;
	second = first;
	first = n;
      }
      else if (n > second) {
	third = second;
	second = n;
      }
      else if (n > third) {
	third = n;
      }
      n = 0;
    }
  if (n > first) { // Include last n
    third = second;
    second = first;
    first = n;
  }
  else if (n > second) {
    third = second;
    second = n;
  }
  else if (n > third) {
    third = n;
  }
  printf("%d\n", first + second + third);
  return 0;
}
