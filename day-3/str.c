// str: functions for dealing with strings
#include <stdio.h>
/*
/* get_line: get input line (with newline).
   returns line length, and 0 on EOF or line length > maxline *
int get_line(char *s, int maxline)
{
  char c;
  int i = 0;
  while ((c = getchar()) != '\n' && c != EOF && ++i < maxline)
    *s++ = c;
  if (c == '\n')
    *s++ = c;
  *s = '\0';
  return i;
}
*/

/* split: splits a string at index n */
char *split(char *s, int n)
{
  return s + n;
}

/* find: return pointer to first occurence of c in s, or NULL */
char *find(char *s, char c)
{
  char ch;
  while ((ch = *s++) != '\0')
    if (ch == c)
      return --s;
  return NULL;
}

