#include "../include/assembler.h"
#include "../include/constants.h"
#include "../include/helpers.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <string.h>

int next_variable_address = 16;

void Diagnostic_free(void *ptr) {
  struct Diagnostic *d = ptr;
  free(d->message);
  free(d);
}

void Instruction_free(void *ptr) {
  struct Instruction *i = ptr;
  if (i->type == C_INSTR) {
    free(i->instruction.cInstruction.dest);
    free(i->instruction.cInstruction.comp);
    free(i->instruction.cInstruction.jump);
  }
  free(i);
};

AssemblerResult *assemble(char *source) {

  Map *dests = Map__create(INITIAL_CAPACITY),
      *comps = Map__create(INITIAL_CAPACITY),
      *jumps = Map__create(INITIAL_CAPACITY);

  init_tables(dests, comps, jumps);

  Vector *diagnostics = Vector__create(Diagnostic_free, INITIAL_CAPACITY),
         *instructions = Vector__create(Instruction_free, INITIAL_CAPACITY);

  Map *symbols = Map__create(INITIAL_CAPACITY);
  init_symbols(symbols);

  Map *unresolved_symbols = Map__create(INITIAL_CAPACITY);

  char line_buf[MAX_LINE];
  int line_num = 1;
  int pc = 0;

  while (get_line(source, line_buf, MAX_LINE)) {

    char *line = strdup(line_buf);
    strip_line_endings(line);
    char *line_no_whitespace = remove_whitespace(line);

    if (is_empty_line(line_no_whitespace)) {
      ++line_num;
      continue;
    }

    struct ParseResult result = parse_line(line_no_whitespace);

    if (result.type == PARSED_A_INSTRUCTION ||
        result.type == PARSED_C_INSTRUCTION)
      ++pc;

    analyze_line(symbols, instructions, diagnostics, unresolved_symbols, dests,
                 comps, jumps, &result, line_num, pc);

    ++line_num;
  }

  resolve_symbols(symbols, unresolved_symbols, instructions, diagnostics);

  AssemblerResult *result = malloc(sizeof(AssemblerResult));
  *result = (AssemblerResult){
      .instructions = instructions,
      .diagnostics = diagnostics,
      .symbols = symbols,
      .dests = dests,
      .comps = comps,
      .jumps = jumps,
  };

  return result;
};