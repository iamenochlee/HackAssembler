#include "../include/assembler.h"
#include "../include/constants.h"
#include "../include/helpers.h"
#include "../include/utils.h"
#include <stdlib.h>

void analyze_line(Map *symbols, Vector *instructions, Vector *diagnostics,
                  Map *unresolved_symbols, Map *dests, Map *comps, Map *jumps,
                  struct ParseResult *result, int line_num, int pc) {

  switch (result->type) {
  case PARSED_COMMENT:
    return;

  case PARSED_INVALID:
    add_diagnostic(diagnostics, ERROR, line_num, result->instruction);
    return;

  case PARSED_LABEL:
    add_symbol(symbols, result->label, pc);
    return;

  case PARSED_A_INSTRUCTION: {
    if (check_if_A_numeric(result->instruction)) {

      union InstructionEntry instr;
      instr.aValue = atoi(result->instruction);
      add_instruction(instructions, A_INSTR, instr);

      free(result->instruction);
      return;
    }

    int sym_value = get_symbol_value(symbols, result->instruction);
    if (sym_value != -1) {

      union InstructionEntry instr;
      instr.aValue = sym_value;
      add_instruction(instructions, A_INSTR, instr);

      free(result->instruction);
      return;
    }

    union InstructionEntry instr;
    instr.aValue = DEFAULT_LABEL_VALUE;
    add_instruction(instructions, A_INSTR, instr);
    add_unresolved_symbol(unresolved_symbols, result->instruction,
                          instructions->count - 1);
    return;
  }

  case PARSED_C_INSTRUCTION: {
    char *dest = malloc(4), *comp = malloc(4), *jump = malloc(4);
    get_dest_comp_jump(result->instruction, dest, comp, jump);

    if (!is_valid_dest(dests, dest)) {
      add_diagnostic(diagnostics, ERROR, line_num, result->instruction);
      return;
    }

    if (!is_valid_comp(comps, comp)) {
      add_diagnostic(diagnostics, ERROR, line_num, result->instruction);
      return;
    }

    if (!is_valid_jump(jumps, jump)) {
      add_diagnostic(diagnostics, ERROR, line_num, result->instruction);
      return;
    }

    union InstructionEntry instr;
    instr.cInstruction.comp = comp;
    instr.cInstruction.dest = dest;
    instr.cInstruction.jump = jump;
    add_instruction(instructions, C_INSTR, instr);

    free(result->instruction);
    return;
  }
  }
}