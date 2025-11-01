#ifndef TYPES_H
#define TYPES_H

typedef struct AssemblerConfig {
  int generate_instructions;
  int debug;
} AssemblerConfig;

enum InstructionType { A_INSTR, C_INSTR };

struct CInstruction {
  char *dest;
  char *comp;
  char *jump;
};

union InstructionEntry {
  int aValue;
  struct CInstruction cInstruction;
};

struct Instruction {
  enum InstructionType type;
  union InstructionEntry instruction;
};

struct Diagnostic {
  int line;
  char *message;
};

#endif