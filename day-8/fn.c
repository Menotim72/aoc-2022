#define MAXLINE 1000

/* upd_vis: used in determine_visibility. updates visibility grid and
   returns new (possibly updated) value for blocking
*/
static int upd_vis(int grid[][MAXLINE], int vis[][MAXLINE],
		   int i1, int i2, int blocking)
{
  if (grid[i1][i2] > blocking) {
    vis[i1][i2] = 1;
    return grid[i1][i2];
  }
  return blocking;
}

/* determine_visibility: sets visibility[i][j] to whether grid[i][j]
   is visible. grid must be size_1 X size_2, and visibility at least
   as big.
*/
void determine_visibility(int grid[][MAXLINE], int visibility[][MAXLINE],
			  int size_1, int size_2)
{
  int blocking, i1, i2;
  for (i1 = 0; i1 < size_1; i1++) {
    blocking = -1;
    for (i2 = 0; i2 < size_2; i2++) // visible from left
      blocking = upd_vis(grid, visibility, i1, i2, blocking);
    blocking = -1;
    for (i2 = size_2 - 1; i2 >= 0; i2--) // visible from right
      blocking = upd_vis(grid, visibility, i1, i2, blocking);
  }
  for (i2 = 0; i2 < size_2; i2++) {
    blocking = -1;
    for (i1 = 0; i1 < size_1; i1++) // visible from above
      blocking = upd_vis(grid, visibility, i1, i2, blocking);
    blocking = -1;
    for (i1 = size_1 - 1; i1 >= 0; i1--) // visible from below
      blocking = upd_vis(grid, visibility, i1, i2, blocking);
  }
}

/* sum_grid: utility, sums all elements in grid size_1 x size_2 */
int sum_grid(int grid[][MAXLINE], int size_1, int size_2)
{
  int total = 0;
  for (int i1 = 0; i1 < size_1; i1++)
    for (int i2 = 0; i2 < size_2; i2++)
      total += grid[i1][i2];
  return total;
}

#include <stdio.h>

/* scenic_score: returns the scenic score of grid[i][j]
   (grid assumed to be size_1 x size_2) */
int scenic_score(int grid[][MAXLINE], int i, int j, int size_1, int size_2)
{
  int c, above, below, left, right;
  above = below = left = right = 0;
  for (c = j + 1; c < size_2; c++) {
    right++;
    if (grid[i][c] >= grid[i][j]) {
      break;
    }
  }
  for (c = j - 1; c >= 0; c--) {
    left++;
    if (grid[i][c] >= grid[i][j])
      break;
  }
  for (c = i + 1; c < size_1; c++) {
    below++;
    if (grid[c][j] >= grid[i][j])
      break;
  }
  for (c = i - 1; c >= 0; c--) {
    above++;
    if (grid[c][j] >= grid[i][j])
      break;
  }
  return above * below * left * right;
}
    
int max(int a, int b)
{
  return a > b ? a : b;
}

#include <stdio.h>

/* get_grid: gets the input grid into an array
   passes size of grid through size_1 and size_2 pointers */
void get_grid(int grid[][MAXLINE], int *size_1, int *size_2)
{
  int j = *size_1 = 0;
  char c;
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      (*size_1)++;
      *size_2 = j;
      j = 0;
    }
    else
      grid[*size_1][j++] = (int) (c - '0');
  }
}
    
