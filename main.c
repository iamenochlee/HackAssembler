#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INSTRUCTION_BITS 16
#define READ_FLAGS "r"
#define TWO_MB (2 << 20)

void *parse_file(FILE *file);
FILE *setup(char *filename);

// instruction pointer, line pointer

int main(int argc, char *argv[])
{

  if (argc != 2)
  {
    fprintf(stderr, "usage: has [-opts] file\n");
    return 1;
  }

  FILE *file = setup(argv[1]);

  parse_file(file);

  return 0;
}

FILE *setup(char *filename)
{

  FILE *file = fopen(filename, READ_FLAGS);

  if (file == NULL)
  {
    perror("Error");
    exit(2);
  }

  return file;
}
