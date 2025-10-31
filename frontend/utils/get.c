#include <string.h>

int get_label(const char *source, char *target) {
  char *start = strstr(source, "(");
  char *end = strstr(source, ")");

  if (start && end && start < end) {
    int length = end - start - 1;
    strncpy(target, start + 1, length);
    target[length] = '\0';
    return 0;
  }

  return 1;
}

void get_dest_comp_jump(char *c_instr, char *dest, char *comp, char *jump) {

  dest[0] = '\0'; // Initialize as empty string
  int dest_in = 1;
  int dest_found = 0;

  while (dest_in < 4) {
    dest_in++;
    if (c_instr[dest_in - 1] == '=') {
      dest_found = 1; // Set the existing variable, don't declare new one
      break;
    }
  }

  if (dest_found) {
    strncpy(dest, c_instr, dest_in - 1);
    dest[dest_in - 1] = '\0'; // Null terminate
  }

  // pick comp, check up to ;, if no = all is comp

  comp[0] = '\0'; // Initialize as empty string
  int comp_start =
      dest_found ? dest_in : 0; // Start after '=' or from beginning
  int comp_len = 0;

  while (c_instr[comp_start] != '\0' && c_instr[comp_start] != ';' &&
         comp_len < 3) {
    comp[comp_len] = c_instr[comp_start];
    comp_len++;
    comp_start++;
  }
  comp[comp_len] = '\0';

  // pick jump after ;
  // Max jump length
  jump[0] = '\0'; // Initialize as empty string
  if (c_instr[comp_start] == ';') {
    strcpy(jump, c_instr + comp_start + 1); // Copy after ';'
  }
}