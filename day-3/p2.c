#include <stdio.h>
#include <string.h>

char find_common(char *s1, char *s2, char *s3);
int priority(char c);

#define MAXLINE 1000

int main()
{
  int total, length;
  char s1[MAXLINE], s2[MAXLINE], s3[MAXLINE];
  total = 0;
  while (fgets(s1, MAXLINE, stdin)
	 && fgets(s2, MAXLINE, stdin)
	 && fgets(s3, MAXLINE, stdin)) {
    total += priority(find_common(s1, s2, s3));
  }
  printf("%d\n", total);
  return 0;
}

