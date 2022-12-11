#include <stdio.h>

void init_relations(void);
void do_round(int wd);
long long int monkey_business(void);

int main()
{
  init_relations();
  for (int i = 1; i <= 10000; i++)
    do_round(0);
  printf("%lld\n", monkey_business());
  return 0;
}
