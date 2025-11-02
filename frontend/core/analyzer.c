#include "../include/assembler.h"
#include "../include/constants.h"
#include "../include/helpers.h"
#include "../include/utils.h"
#include <stdlib.h>

void analyze_line(AssemblerConfig config, Map *symbols, void *instructions,
                  Vector *diagnostics, Map *unresolved_symbols, Map *dests,
                  Map *comps, Map *jumps, struct ParseResult *result,
                  int line_num, int pc) {

  switch (result->type) {
  case PARSED_COMMENT:
    return;

  case PARSED_INVALID:
    add_diagnostic(diagnostics, line_num, result->instruction);
    return;

  case PARSED_LABEL:
    add_symbol(symbols, result->label, pc);
    return;

  case PARSED_A_INSTRUCTION: {
    if (check_if_A_numeric(result->instruction)) {

      union InstructionEntry instr;
      instr.aValue = atoi(result->instruction);

      if (config.generate_instructions && !diagnostics->count) {
        add_instruction(instructions, A_INSTR, instr);
      }

      free(result->instruction);
      return;
    }

    int sym_value = get_symbol_value(symbols, result->instruction);
    if (sym_value != -1) {

      union InstructionEntry instr;
      instr.aValue = sym_value;

      if (config.generate_instructions && !diagnostics->count) {
        add_instruction(instructions, A_INSTR, instr);
      }

      free(result->instruction);
      return;
    }

    union InstructionEntry instr;
    instr.aValue = DEFAULT_LABEL_VALUE;

    if (config.generate_instructions && !diagnostics->count) {
      Vector *v_instr = (Vector *)instructions;
      add_instruction(instructions, A_INSTR, instr);
      add_unresolved_symbol(unresolved_symbols, result->instruction,
                            v_instr->count - 1);
      return;
    }

    add_unresolved_symbol(unresolved_symbols, result->instruction,
                          IGNORE_INSTR_EDIT_SINCE_NO_INSTRUCTIONS);
    return;
  }

  case PARSED_C_INSTRUCTION: {
    char *dest = malloc(4), *comp = malloc(4), *jump = malloc(4);
    get_dest_comp_jump(result->instruction, dest, comp, jump);

    int valid_dest = is_valid_dest(dests, dest);
    int valid_comp = is_valid_comp(comps, comp);
    int valid_jump = is_valid_jump(jumps, jump);

    if (!valid_dest || !valid_comp || !valid_jump) {
      add_diagnostic(diagnostics, line_num, result->instruction);
      free(dest);
      free(comp);
      free(jump);
      return;
    }

    union InstructionEntry instr;
    instr.cInstruction.dest = dest;
    instr.cInstruction.comp = comp;
    instr.cInstruction.jump = jump;

    if (config.generate_instructions && !diagnostics->count) {
      add_instruction(instructions, C_INSTR, instr);
    } else {
      free(dest);
      free(comp);
      free(jump);
    }

    free(result->instruction);
    return;
  }
  }
}