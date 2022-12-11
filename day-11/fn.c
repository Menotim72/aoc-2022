#include <stdio.h>
#include <stdlib.h>

#define MAXITEMS 64

#define MODULO_PRODUCT (2*3*5*7*11*13*17*19)

/* error: prints error message and exits */
void error(char *msg)
{
  fprintf(stderr, "error: %s\n", msg);
  exit(1);
}

enum operation {
  ADDITION,
  MULTIPLICATION,
  SQUARING
};

typedef struct Monkey {
  long long int items[MAXITEMS];
  int item_count;
  int operation;
  int op_factor;
  int div_test;
  struct Monkey *throw_if_true;
  struct Monkey *throw_if_false;
  int inspection_count;
} Monkey;

/* add_item: add item to monkey's inventory */
void add_item(Monkey *monkey, long long int item)
{
  if (monkey->item_count == MAXITEMS)
    error("too many items");
  monkey->items[monkey->item_count++] = item;
}

/* apply_operation: calculated worry level of an item */
long long int apply_operation(long long int item, int operation,
			 int op_factor, int worry_diminishes)
{
  long long int opped;
  switch (operation) {
  case ADDITION: opped = item + op_factor; break;
  case MULTIPLICATION: opped = item * op_factor; break;
  case SQUARING: opped = item * item; break;
  default: error("invalid operation");
  }
  return worry_diminishes ? opped / 3 : opped % MODULO_PRODUCT;
}

/* inspect_items: inspect monkey's items and throw to others */
void inspect_items(Monkey *monkey, int worry_diminishes)
{
  long long int opped;
  for (int i = 0; i < monkey->item_count; i++) {
    opped = apply_operation(monkey->items[i],
			    monkey->operation,
			    monkey->op_factor,
			    worry_diminishes);
    add_item(opped % monkey->div_test == 0 ?
	     monkey->throw_if_true : monkey->throw_if_false,
	     opped);
  }
  monkey->inspection_count += monkey->item_count;
  monkey->item_count = 0;
}


#define MONKEY_COUNT 8

Monkey monkeys[MONKEY_COUNT] = {
  { {99, 67, 92, 61, 83, 64, 98}, 7, 
    MULTIPLICATION, 17, 3, NULL, NULL, 0},
  { {78, 74, 88, 89, 50}, 5,
    MULTIPLICATION, 11, 5, NULL, NULL, 0},
  { {98, 91}, 2,
    ADDITION, 4, 2, NULL, NULL, 0},
  { {59, 72, 94, 91, 79, 88, 94, 51}, 8,
    SQUARING, 2, 13, NULL, NULL, 0},
  { {95, 72, 78}, 3,
    ADDITION, 7, 11, NULL, NULL, 0},
  { {76}, 1,
    ADDITION, 8, 17, NULL, NULL, 0},
  { {69, 60, 53, 89, 71, 88}, 6,
    ADDITION, 5, 19, NULL, NULL, 0},
  { {72, 54, 63, 80}, 4,
    ADDITION, 3, 7, NULL, NULL, 0}
};

int relations[MONKEY_COUNT][2] = {
  4, 2,
  3, 5,
  6, 4,
  0, 5,
  7, 6,
  0, 2,
  7, 1,
  1, 3
};

/*
#define MONKEY_COUNT 4

Monkey monkeys[MONKEY_COUNT] = {
  { {79, 98}, 2,
    MULTIPLICATION, 19, 23, NULL, NULL, 0 },
  { {54, 65, 75, 74}, 4,
    ADDITION, 6, 19, NULL, NULL, 0 },
  { {79, 60, 97}, 3,
    SQUARING, 2, 13, NULL, NULL, 0 },
  { {74}, 1,
    ADDITION, 3, 17, NULL, NULL, 0 }
};

int relations[MONKEY_COUNT][2] = {
  2, 3,
  2, 0,
  1, 3,
  0, 1
};
*/
#define iter_monkeys for (int i = 0; i < MONKEY_COUNT; i++)

/* init_relations: initializes monkey relationships */
void init_relations(void)
{
  iter_monkeys {
    monkeys[i].throw_if_true = &monkeys[relations[i][0]];
    monkeys[i].throw_if_false = &monkeys[relations[i][1]];
  }
}

/* do_round: operate the monkeys for an entire round */
void do_round(int worry_diminishes)
{
  iter_monkeys 
    inspect_items(&monkeys[i], worry_diminishes);
}

/* monkey_business: calculate monkey business level */
long long int monkey_business(void)
{
  long long int first, second;
  first = second = 0;
  iter_monkeys 
    if (monkeys[i].inspection_count > first) {
      second = first;
      first = monkeys[i].inspection_count;
    } else if (monkeys[i].inspection_count > second)
      second = monkeys[i].inspection_count;
  return first * second;
}
    
void display_monkey_start(void)
{
   iter_monkeys {
    printf("Monkey %d:", i);
    printf("  Starting items:");
    for (int j = 0; j < monkeys[i].item_count; j++)
      printf(" %lld,", monkeys[i].items[j]);
    printf("\n  Operation: new = old %c %d\n",
	   monkeys[i].operation == ADDITION ? '+' :
	   (monkeys[i].operation == MULTIPLICATION ? '*' : '^'),
	   monkeys[i].op_factor);
    printf("  Test: divisible by %d\n", monkeys[i].div_test);
    printf("    If true: throw to monkey %d\n", relations[i][0]);
    printf("    If false: throw to monkey %d\n\n", relations[i][1]);
  }
}

void display_after_round(int round) {
  printf("After round %d, the monkeys are holding items with these worry levels:\n", round);
  iter_monkeys {
    printf("Monkey %d:", i);
    for (int j = 0; j < monkeys[i].item_count; j++)
      printf(" %lld,", monkeys[i].items[j]);
    printf("\n");
  }
  printf("\n");
}

void display_inspections(void) {
  iter_monkeys {
    printf("Monkey %d inspected items %d times \n", i, monkeys[i].inspection_count);
  }
  printf("\n");
}
