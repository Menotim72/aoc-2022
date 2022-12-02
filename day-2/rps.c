// rock is 0, paper is 1, scissors is 2
// lose is 0, draw is 1, win is 2

#include <stdio.h>

/* cmp: does my beat other? */
int cmp(int my, int other)
{
  // if I used 3 instead of 4 it would correct the negative numbers
  // so the result would be 0 in a draw, 1 in a win and 2 in a loss
  // because 2 == -1 mod 3
  return (my - other + 4) % 3;
}

/* choice: what should I do for this result? */
int choice(int other, int win)
{
  // mod 3: win = my - other + 4 -> my = win + other - 4
  // and 2 == -1 == -4 mod 3 to avoid negatives
  return (win + other + 2) % 3;
}

/* score: how much did I score? */
int score(int my, int win)
{
  // straightforward
  return 3 * win + my + 1;
}

/* reads a line into the pointers */
int read_line_to_pt(int *my_pt, int *other_pt)
{
  char c = getchar();
  if (c == EOF) { return 0; }
  *other_pt = c - 'A';
  getchar();
  *my_pt = getchar() - 'X';
  getchar();
}
