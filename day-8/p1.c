#include <stdio.h>

#define MAXLINE 1000

void get_grid(int grid[][MAXLINE], int *size_1, int *size_2);
void determine_visibility(int grid[][MAXLINE], int visib[][MAXLINE],
			  int size_1, int size_2);
int sum_grid(int grid[][MAXLINE], int size_1, int size_2);

int main()
{
  int size_1, size_2, grid[MAXLINE][MAXLINE], visibility[MAXLINE][MAXLINE];
  get_grid(grid, &size_1, &size_2);
  determine_visibility(grid, visibility, size_1, size_2);
  printf("%d\n", sum_grid(visibility, size_1, size_2));
}
