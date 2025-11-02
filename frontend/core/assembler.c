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

AssemblerResult assemble(char *source, AssemblerConfig config) {

  Map *dests = Map__create(INITIAL_CAPACITY, INITIAL_DESTS_COUNT),
      *comps = Map__create(INITIAL_CAPACITY, INITIAL_COMPS_COUNT),
      *jumps = Map__create(INITIAL_CAPACITY, INITIAL_JUMPS_COUNT);

  Map *symbols = Map__create(INITIAL_CAPACITY, INITIAL_SYMBOLS_COUNT);

  init_tables(dests, comps, jumps);
  init_symbols(symbols);

  Vector *diagnostics = Vector__create(Diagnostic_free, INITIAL_CAPACITY);

  Vector *instructions = NULL;
  if (config.generate_instructions) {
    instructions = Vector__create(Instruction_free, INITIAL_CAPACITY);
  }

  Map *unresolved_symbols =
      Map__create(INITIAL_CAPACITY, DEFAULT_START_FREE_INDEX);

  char line_buf[MAX_LINE];
  int line_num = 1;
  int pc = 0;

  while (get_line(source, line_buf, MAX_LINE)) {

    char *line = sanitize_line(line_buf);
    if (is_empty_line(line)) {
      ++line_num;
      free(line);
      continue;
    }

    struct ParseResult result = parse_line(line);

    if (result.type == PARSED_A_INSTRUCTION ||
        result.type == PARSED_C_INSTRUCTION)
      ++pc;

    analyze_line(config, symbols, instructions, diagnostics, unresolved_symbols,
                 dests, comps, jumps, &result, line_num, pc);

    ++line_num;
  }

  resolve_symbols(config, symbols, unresolved_symbols, instructions,
                  diagnostics);

  AssemblerResult result = {
      .instructions = instructions,
      .diagnostics = diagnostics,
      .symbols = symbols,
      .dests = dests,
      .comps = comps,
      .jumps = jumps,
  };

  return result;
};

void AssemblerResult__free(AssemblerResult *result, AssemblerConfig config) {

  if (config.generate_instructions) {
    Vector__free(result->instructions);
  }
  Vector__free(result->diagnostics);

  Map__free(result->symbols);
  Map__free(result->dests);
  Map__free(result->comps);
  Map__free(result->jumps);
}