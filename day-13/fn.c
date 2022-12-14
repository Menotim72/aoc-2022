typedef struct List {
  void *val;
  List *next;
} List;

#include <stdlib.h>

void push_int(List list, int val) {
  while (list.next)
    list = *list.next;
  List *new = (List *) malloc(sizeof List);
  new->val = &val;
  list.next = new;
}

void push_list(List list, List val) {
}
