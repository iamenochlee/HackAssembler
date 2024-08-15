#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"

// handle cases of \r

FILE *open_file(char *filename);

void setup(FILE *);
void add_label(char *lname, int lvalue);

int pc_iln[MAX_LINE];

int label_count = 1;
struct Label LabelTable[MAX_LINE] = {{"R0", 0}};

int main(int argc, char *argv[])
{

  if (argc != 2)
  {
    fprintf(stderr, "usage: has [-opts] file\n");
    return 1;
  }

  FILE *file = open_file(argv[1]);

  setup(file);

  return 0;
}

FILE *open_file(char *filename)
{

  FILE *file = fopen(filename, READ_FLAGS);

  if (file == NULL)
  {
    perror("Error");
    exit(2);
  }

  return file;
}

void get_label(const char *source, char *target)
{
  char *start = strstr(source, "(");
  char *end = strstr(source, ")");

  if (start && end && start < end)
  {
    int length = end - start - 1;
    strncpy(target, start + 1, length);
    target[length] = '\0';
  }
}

void setup(FILE *file)
{

  int ln = 0;
  int pc = 0;

  char line[MAX_LINE];
  while (fgets(line, sizeof(line), file))
  {
    ln++;

    if (!(line[0] == '/' && line[1] == '/') && !(line[0] == '\n' || line[0] == '\0' || line[0] == '\r'))
    {
      pc++;
      pc_iln[pc] = ln;

      if (line[0] == '(')
      {

        char lname[MAX_LINE];
        get_label(line, lname);
        add_label(lname, pc);
      }
    }
  }

  // get line in the file
  // store line count
  // store pc

  // if an instruction add to pc_iln
  // increment pc

  // check if label
  // if label
  // name: label. value=pc
}
