#define MAXNAME 100
#define MAXCHILDREN 1000
#define MAXLINE 1000

struct Dir {
  char *name; // directory name
  int size;           // size of files
  struct Dir *parent;          // parent directory
  struct Dir *children[MAXCHILDREN]; // children directories
  int children_len; // length of children
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* find_child: find subdirectory name of parent. handles .. as well. */
struct Dir *find_child(struct Dir *parent, char *name)
{
  if (!strcmp(name, "..")) // parent directory
    return parent->parent;
  for (int i = 0; i < parent->children_len; i++)
    if (!strcmp(name, parent->children[i]->name))
      return parent->children[i];
}

/* add_child: add subdirectory to a directory */
void add_child(struct Dir *dir, char *name)
{
  if (dir->children_len == MAXCHILDREN) {
    fprintf(stderr, "error: no more space for subdirectories\n");
    exit(1);
  }
  dir->children[dir->children_len] = malloc(sizeof(struct Dir));
  dir->children[dir->children_len]->name = name;
  dir->children[dir->children_len]->parent = dir;
}

/* get_input: parses input.txt and returns root dir */
struct Dir get_input()
{
  struct Dir root = { // root directory
    "/", 0, NULL
  };
  struct Dir *cd = &root; // current directory
  char line[MAXLINE], tempname[MAXLINE], *name;
  int size;
  fgets(line, MAXLINE, stdin); // ignores first line
  while (fgets(line, MAXLINE, stdin)) {
    if (sscanf(line, "$ cd %s", tempname)) {
      printf("Changing to directory: %s\n", tempname);
      //cd = find_child(cd, tempname);
    }
    else if (sscanf(line, "dir %s", tempname)) {
      printf("Creating directory: %s\n", tempname);
      name = malloc(sizeof tempname);
      strcpy(tempname, name);
      add_child(cd, name);
    }
    else if (sscanf(line, "%d %s", &size, tempname)) {
      printf("Adding file of size: %d\n", size);
      //cd->size += size;
    }
  }
  return root;    
}

int main()
{
  struct Dir d = get_input();
  printf("%s %d\n", d.name, d.size);
  struct Dir *ch = find_child(&d, "jgvf");
  printf("%d\n", ch->size);
  return 0;
}
