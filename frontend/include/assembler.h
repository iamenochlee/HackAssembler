#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "structures.h"
#include "types.h"

typedef struct AssemblerResult {
  Vector *instructions;
  Vector *diagnostics;
  Map *symbols;
  Map *dests, *comps, *jumps;
} AssemblerResult;

AssemblerResult *assemble(char *source);

enum LineType {
  PARSED_A_INSTRUCTION,
  PARSED_C_INSTRUCTION,
  PARSED_LABEL,
  PARSED_COMMENT,
  PARSED_INVALID
};

struct ParseResult {
  enum LineType type;
  union {
    char *instruction;
    char *label;
  };
};

struct ParseResult parse_line(char *line);
void analyze_line(Map *symbols, Vector *instructions, Vector *diagnostics,
                  Map *unresolved_symbols, Map *dests, Map *comps, Map *jumps,
                  struct ParseResult *result, int line_num, int pc);

#endif