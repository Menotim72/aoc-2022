#include <stdlib.h>

enum direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

// x-y position 
typedef struct Pos {
  int x;
  int y;
} Pos;

/* move: move one of head or tail without the other */
Pos move(Pos pos, int direction)
{
  switch (direction) {
  case UP: pos.y++; break;
  case DOWN: pos.y--; break;
  case LEFT: pos.x--; break;
  case RIGHT: pos.x++; break;
  }
  return pos;
}

/* drag: says where tail will end up if it is dragged by head */
Pos drag(Pos tail, Pos head)
{
  int dis_x = head.x - tail.x;
  int dis_y = head.y - tail.y;
  if (abs(dis_x) >  1 || abs(dis_y) > 1) {
    if (dis_x > 0) tail.x += 1;
    if (dis_x < 0) tail.x -= 1;
    if (dis_y > 0) tail.y += 1;
    if (dis_y < 0) tail.y -= 1;
  }
  return tail;
}

/* move_arr: move array of length len in direction dir */
void move_arr(Pos arr[], int len, int dir)
{
  if (len == 0) return;
  arr[0] = move(arr[0], dir);
  for (int i = 1; i < len; i++)
    arr[i] = drag(arr[i], arr[i-1]);
}

/* add: add to a list of unique positions, return new len */
int add(Pos ls[], int len, Pos pos)
{
  for (int i = 0; i < len; i++) 
    if (ls[i].x == pos.x && ls[i].y == pos.y)
      return len;
  ls[len] = pos;
  return len + 1;
}

/* parse_dir: parse a direction from a char */
int parse_dir(char c)
{
  switch (c) {
  case 'U': return UP;
  case 'D': return DOWN;
  case 'L': return LEFT;
  case 'R': return RIGHT;
  }
}

#include <stdio.h>

#define MAXPOS 10000
#define MAXLINE 10

/* simulate_rope: simulates a rope from input and tracks the positions
   visited by the rope's tail */
int simulate_rope(int length) {
  char c;
  int amount, dir, positions;
  positions = 1;
  Pos rope[length];
  for (int i = 0; i < length; i++)
    rope[i].x = rope[i].y = 0;     // initializes rope
  Pos poslist[MAXPOS];
  poslist[0] = rope[length-1];
  char line[MAXLINE];
  while (fgets(line, MAXLINE, stdin)) {
    sscanf(line, "%c %d", &c, &amount);
    dir = parse_dir(c);
    for (int i = 0; i < amount; i++) {
      move_arr(rope, length, dir);
      positions = add(poslist, positions, rope[length-1]);
    }
  }
  printf("%d\n", positions);
}
