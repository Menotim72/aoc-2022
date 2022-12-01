#include <stdio.h>

#define MAXLINE 100

char linebfr[MAXLINE];

int get_number_line(void);

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
}

#include <stdlib.h>

int get_number_line(void)
{
  char c;
  int i = 0;
  while ((c = getchar()) != '\n' && c != EOF) {
    linebfr[i++] = c;
  }
  if (c == EOF)
    return -1;
  else if (i == 0)
    return 0;
  else {
    linebfr[i] = '\0';
    return atoi(linebfr);
  }
}
  
