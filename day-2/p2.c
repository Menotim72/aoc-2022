#include <stdio.h>

int read_line_to_pt(int *win, int *other);
int choice(int other, int win);
int score(int my, int win);

int main()
{
  int win, other, total;
  while (read_line_to_pt(&win, &other)) {
    total += score(choice(other, win), win);
  }
  printf("%d\n", total);
  return 0;
}
