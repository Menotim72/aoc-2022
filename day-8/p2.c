#include <stdio.h>

#define MAXLINE 1000

void get_grid(int grid[][MAXLINE], int *size_1, int *size_2);
int scenic_score(int grid[][MAXLINE], int i, int j, int size_1, int size_2);
int max(int a, int b);

int main()
{
  int max_score = 0, size_1, size_2, grid[MAXLINE][MAXLINE];
  get_grid(grid, &size_1, &size_2);
  for (int i = 0; i < size_1; i++)
    for (int j = 0; j < size_2; j++)
      max_score = max(max_score, scenic_score(grid, i, j, size_1, size_2));
  printf("%d\n", max_score);
}
