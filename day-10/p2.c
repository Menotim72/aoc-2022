#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100

int cycles;

void print_sprite_pos(int x)
{
  for (int i = 0; i <= 40; i++)
    putchar(abs(x - i) <= 1 ? '#' : '.');
}

/* draw: draws a pixel and counts up a cycle */
void draw(int x)
{
  cycles++;
  
  if (abs(x + 1 - (cycles % 40)) <= 1) printf("█");
  else printf("░");
  if (cycles % 40 == 0)
    putchar('\n');
}

int main()
{
  char linebfr[MAXLINE];
  int x, added;
  x = 1;
  while (fgets(linebfr, MAXLINE, stdin)) {
    draw(x);
    if (sscanf(linebfr, "addx %d", &added)) draw(x); 
    else if (sscanf(linebfr, "noop")) added = 0;
    else continue;

    x += added;
  }
}
