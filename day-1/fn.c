#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100

static char linebfr[MAXLINE];

/* Gets a line containing only an integer */
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
 
