#include "../header.h"

extern LabelArray label_table;
extern int next_variable_address;

int allocate_variable(char *variable_name)
{
  // Allocate new address for the variable
  int allocated_address = next_variable_address++;
  add_dynamic_label(&label_table, variable_name, allocated_address);

  return allocated_address;
}

int get_instruction_type(char *line)
{
  if (line[0] == '@')
  {
    return 0;
  }

  return 1;
}

int check_if_comment(char *line)
{
  if ((line[0] == '/' && line[1] == '/') ||
      (line[0] == '\0')) // Empty line after stripping
  {
    return 1;
  }
  return 0;
}

int check_if_label(char *line)
{
  if (line[0] == '(')
  {
    return 1;
  }
  return 0;
}

int check_if_A_numeric(char *line)
{
  int i = 1;
  while (line[i] != '\0')
  {
    if ((line[i] < '0') || (line[i] > '9')) // Use character constants
    {
      return 0;
    }
    i++;
  }

  return 1;
}

int check_if_known_label(char *label)
{
  // Use the dynamic array's data and size
  int res = get_Value(label_table.data, label_table.size, label);
  if (res == -1)
    return 0;

  return 1;
}

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

int get_label(const char *source, char *target)
{
  char *start = strstr(source, "(");
  char *end = strstr(source, ")");

  if (start && end && start < end)
  {
    int length = end - start - 1;
    strncpy(target, start + 1, length);
    target[length] = '\0';
    return 0;
  }

  return 1;
}