#include <stdio.h>

#define MAXLINE 100

int main()
{
  char linebfr[MAXLINE];
  int x, cycles, added, total_sig, next_cycle;
  total_sig = cycles = 0;
  x = 1;
  next_cycle = 20;
  while (fgets(linebfr, MAXLINE, stdin)) {
    cycles++;
    if (sscanf(linebfr, "addx %d", &added)) cycles++; 
    else if (sscanf(linebfr, "noop")) added = 0;
    else continue;

    if (cycles >= next_cycle) {
      total_sig += x * next_cycle;
      next_cycle += 40;
    }

    x += added;
  }
  printf("%d\n", total_sig);
  return 0;
}
