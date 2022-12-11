#include <stdio.h>

void init_relations(void);
void do_round(int wd);
int monkey_business(void);

int main()
{
  init_relations();
  for (int i = 1; i <= 20; i++)
    do_round(1);
  printf("%d\n", monkey_business());
  return 0;
}
