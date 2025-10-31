#include "../include/assembler.h"
#include "../include/constants.h"
#include "../include/utils.h"
#include <stdlib.h>

struct ParseResult parse_line(char *line) {

  struct ParseResult result;

  if (check_if_comment(line)) {
    result.type = PARSED_COMMENT;
    free(line);
    return result;
  }

  if (check_if_label(line)) {
    char *label = malloc(MAX_LINE);

    if (!get_label(line, label)) {
      result.type = PARSED_INVALID;
      free(line);
      return result;
    };

    result.type = PARSED_LABEL;
    result.label = label;
    free(line);
    return result;
  }

  if(!check_instruction_type(line)) {

    result.type = PARSED_A_INSTRUCTION;
    result.instruction = line;
    return result;
  }
  
  result.type = PARSED_C_INSTRUCTION;
  result.instruction = line;
  return result;
}