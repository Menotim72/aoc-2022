#include <string.h>

/* find_repeat: find character that appears in both halves of line */
char find_repeat(char *line, int length)
{
  char c;
  int half = (length - 1) / 2;
  char *second = (line + half);
  for (int i = 0; i < half; i++)
    if (strchr(second, *line++))
      return *--line;
}

/* priority: item priority. no error checking. */
int priority(char c)
{
  if (c >= 'a' && c <= 'z')
    return c - 'a' + 1;
  else
    return c - 'A' + 27;
}

#include <stdio.h>

/* find_common: find the common character */
char find_common(char *s1, char *s2, char *s3)
{
  char c;
  while ((c = *s1++) != '\0' && c != '\n') {
    if (strchr(s2, c) && strchr(s3, c)) {
      return c;
    }
  }
  printf("not found\n");
}
