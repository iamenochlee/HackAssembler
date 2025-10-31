#ifndef TYPES_H
#define TYPES_H

enum InstructionType { A_INSTR, C_INSTR };
enum DiagnosticType { ERROR, WARNING };

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
  enum DiagnosticType type;
  int line;
  char *message;
};

#endif