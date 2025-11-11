#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>

// Assembler configuration
typedef struct AssemblerConfig {
  int generate_instructions;
  int debug;
} AssemblerConfig;

// Instruction types
enum InstructionType { A_INSTR, C_INSTR };

// C-instruction components
struct CInstruction {
  char *dest;
  char *comp;
  char *jump;
};

// Instruction data (A or C instruction)
union InstructionEntry {
  int aValue;
  struct CInstruction cInstruction;
};

// Complete instruction
struct Instruction {
  enum InstructionType type;
  union InstructionEntry instruction;
};

//  Diagnostic
struct Diagnostic {
  int line;
  char *message;
};

// Line reader structure to track state without static variables
typedef struct {
  const char *source;
  size_t idx;
} LineReader;

#endif