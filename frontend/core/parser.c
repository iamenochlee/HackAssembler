#include "../include/assembler.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <string.h>

struct ParseResult parse_line(char *line) {

  struct ParseResult result;

  if (check_if_comment(line)) {
    result.type = PARSED_COMMENT;
    free(line);
    return result;
  }

  if (check_if_label(line)) {
    // accounting for () that will be removed
    char *label = malloc(strlen(line) - 1);

    if (!get_label(line, label)) {
      free(label);
      result.type = PARSED_INVALID;
      result.instruction = line;
      return result;
    }

    // Empty labels () are invalid
    if (label[0] == '\0') {
      free(label);
      result.type = PARSED_INVALID;
      result.instruction = line;
      return result;
    }

    result.type = PARSED_LABEL;
    result.label = label;
    free(line);
    return result;
  }

  if (!check_instruction_type(line)) {

    result.type = PARSED_A_INSTRUCTION;

    char *a_instr = malloc(strlen(line));
    strcpy(a_instr, line + 1);
    free(line);

    result.instruction = a_instr;
    return result;
  }

  result.type = PARSED_C_INSTRUCTION;
  result.instruction = line;
  return result;
}