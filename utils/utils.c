#include "header.h"

void int_to_bin(int n, char *ptr, int start_index, int end_index)
{

  for (int i = end_index; n > 0 && i >= start_index; i--)
  {
    int bin = n % 2;

    ptr[i] = '0' + bin;

    n = n >> 1;
  }
}

void copy_instr_to_buf(int startbytes, char *instr_line, char *buf)
{
  strcpy(buf + startbytes, instr_line);
}

char *remove_whitespace(const char *line)
{
  if (line == NULL)
  {
    return NULL;
  }

  // Calculate length needed (excluding whitespace)
  int len = strlen(line);
  int new_len = 0;
  for (int i = 0; i < len; i++)
  {
    if (!isspace(line[i]))
    {
      new_len++;
    }
  }

  // Allocate memory for new string
  char *result = malloc(new_len + 1);
  if (result == NULL)
  {
    return NULL;
  }

  // Copy non-whitespace characters
  int j = 0;
  for (int i = 0; i < len; i++)
  {
    if (!isspace(line[i]))
    {
      result[j++] = line[i];
    }
  }
  result[j] = '\0';

  return result;
}

void strip_line_endings(char *line)
{
  if (line == NULL)
    return;

  int len = strlen(line);
  while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
  {
    line[--len] = '\0';
  }
}
