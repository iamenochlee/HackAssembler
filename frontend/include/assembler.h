#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "structures.h"
#include "types.h"

enum LineType {
  PARSED_COMMENT,
  PARSED_INVALID,
  PARSED_LABEL,
  PARSED_A_INSTRUCTION,
  PARSED_C_INSTRUCTION
};

struct ParseResult {
  enum LineType type;
  union {
    char *instruction;
    char *label;
  };
};

typedef struct AssemblerResult {
  Vector *instructions;
  Vector *diagnostics;
  Map *symbols;
  Map *dests, *comps, *jumps;
} AssemblerResult;

// NOTE: if `config.generate_instructions` is false,
// `AssemblerResult.instructions` will be NULL
AssemblerResult assemble(char *source, AssemblerConfig config);
void AssemblerResult__free(AssemblerResult *result, AssemblerConfig config);

struct ParseResult parse_line(char *line);
void analyze_line(AssemblerConfig config, Map *symbols, void *instructions,
                  Vector *diagnostics, Map *unresolved_symbols, Map *dests,
                  Map *comps, Map *jumps, struct ParseResult *result,
                  int line_num, int pc);

#endif