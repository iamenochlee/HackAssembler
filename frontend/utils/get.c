#include "../include/types.h"
#include <stdlib.h>
#include <string.h>

int get_label(const char *source, char *target) {
  char *start = strstr(source, "(");
  char *end = strstr(source, ")");

  if (start && end && start < end) {
    int length = end - start - 1;
    strncpy(target, start + 1, length);
    target[length] = '\0';
    return 1;
  }

  return 0;
}

struct CInstruction parse_c_instruction(const char *c_instr) {
  struct CInstruction result;

  // Allocate memory for each component
  result.dest = malloc(4);
  result.comp = malloc(4);
  result.jump = malloc(4);

  if (!result.dest || !result.comp || !result.jump) {
    // On allocation failure, set to empty strings and return
    if (result.dest) {
      result.dest[0] = '\0';
    } else {
      result.dest = NULL;
    }
    if (result.comp) {
      result.comp[0] = '\0';
    } else {
      result.comp = NULL;
    }
    if (result.jump) {
      result.jump[0] = '\0';
    } else {
      result.jump = NULL;
    }
    return result;
  }

  // Initialize as empty strings
  result.dest[0] = '\0';
  result.comp[0] = '\0';
  result.jump[0] = '\0';

  // Parse destination (before '=')
  int dest_in = 1;
  int dest_found = 0;

  while (dest_in < 4) {
    dest_in++;
    if (c_instr[dest_in - 1] == '=') {
      dest_found = 1;
      break;
    }
  }

  if (dest_found) {
    strncpy(result.dest, c_instr, dest_in - 1);
    result.dest[dest_in - 1] = '\0'; // Null terminate
  }

  // Parse computation (between '=' and ';' or entire string if no '=')
  int comp_start =
      dest_found ? dest_in : 0; // Start after '=' or from beginning
  int comp_len = 0;

  while (c_instr[comp_start] != '\0' && c_instr[comp_start] != ';' &&
         comp_len < 3) {
    result.comp[comp_len] = c_instr[comp_start];
    comp_len++;
    comp_start++;
  }
  result.comp[comp_len] = '\0';

  // Parse jump (after ';')
  if (c_instr[comp_start] == ';') {
    strncpy(result.jump, c_instr + comp_start + 1,
            3);            // Copy after ';', max 3 chars
    result.jump[3] = '\0'; // Ensure null termination
  }

  return result;
}