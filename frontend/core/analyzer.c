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

    if (!*result->instruction) {
      add_diagnostic(diagnostics, line_num, result->instruction);
      return;
    }

    if (check_if_A_numeric(result->instruction)) {

      union InstructionEntry instr;
      instr.aValue = atoi(result->instruction);

      if (config.generate_instructions && !diagnostics->size) {
        add_instruction(instructions, A_INSTR, instr);
      }

      free(result->instruction);
      return;
    }

    int sym_value = get_symbol_value(symbols, result->instruction);
    if (sym_value != -1) {

      union InstructionEntry instr;
      instr.aValue = sym_value;

      if (config.generate_instructions && !diagnostics->size) {
        add_instruction(instructions, A_INSTR, instr);
      }

      free(result->instruction);
      return;
    }

    union InstructionEntry instr;
    instr.aValue = DEFAULT_LABEL_VALUE;

    if (config.generate_instructions && !diagnostics->size) {
      Vector *v_instr = (Vector *)instructions;
      add_instruction(instructions, A_INSTR, instr);
      add_unresolved_symbol(unresolved_symbols, result->instruction,
                            v_instr->size - 1);

    } else {
      add_unresolved_symbol(unresolved_symbols, result->instruction,
                            IGNORE_INSTR_EDIT_SINCE_NO_INSTRUCTIONS);
    }
    return;
  }

  case PARSED_C_INSTRUCTION: {
    struct CInstruction c_instr = parse_c_instruction(result->instruction);

    int valid_dest = is_valid_dest(dests, c_instr.dest);
    int valid_comp = is_valid_comp(comps, c_instr.comp);
    int valid_jump = is_valid_jump(jumps, c_instr.jump);

    // comp is always required
    // If dest is absent, jump must be present
    int no_dest = (c_instr.dest[0] == '\0');
    int no_jump = (c_instr.jump[0] == '\0');

    if (!valid_dest || !valid_comp || !valid_jump || (no_dest && no_jump)) {
      add_diagnostic(diagnostics, line_num, result->instruction);
      free(c_instr.dest);
      free(c_instr.comp);
      free(c_instr.jump);
      return;
    }

    union InstructionEntry instr;
    instr.cInstruction = c_instr;

    if (config.generate_instructions && !diagnostics->size) {
      add_instruction(instructions, C_INSTR, instr);
    } else {
      free(c_instr.dest);
      free(c_instr.comp);
      free(c_instr.jump);
    }

    free(result->instruction);
    return;
  }
  }
}