#include <stdio.h>

int read_line_to_pt(int *my, int *other);
int cmp(int my, int other);
int score(int my, int win);

int main()
{
  int my, other, total;
  while (read_line_to_pt(&my, &other)) {
    total += score(my, cmp(my, other));
  }
  printf("%d\n", total);
  return 0;
}
