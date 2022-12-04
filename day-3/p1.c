#include <stdio.h>
#include <string.h>

char find_repeat(char *line, int length);
int priority(char c);

#define MAXLINE 1000

int main()
{
  int total, length;
  char line[MAXLINE];
  total = 0;
  while (fgets(line, MAXLINE, stdin)) {
    length = strlen(line);
    total += priority(find_repeat(line, length));
  }
  printf("%d\n", total);
  return 0;
}
