
/* findback: searches for c backwards in s.
   if it is not found in the last max characters, returns 0.
   searches backwards from len; if r is returned, s[len-r] == c
*/
int findback(char s[], char c, int len, int max)
{
  for (int i = 1; i <= max; i++)
    if (s[len-i] == c)
      return i;
  return 0;
}
  
#include <stdio.h>

#define MAXSIGNAL 8192

int main_fn(int len)
{
  char signal[MAXSIGNAL];
  int nr = 0; // non repeated characters
  int i = 0;
  int fb;
  while (nr < len) {
    signal[i] = getchar();
    if (fb = findback(signal, signal[i], i, nr))
      nr = fb;
    else
      nr++;
    i++;
  }
  printf("%d\n", i);
}
