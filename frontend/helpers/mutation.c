#include "../include/helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int next_variable_address;

void add_symbol(Map *symbols, const char *label, int value) {
  Map__add(symbols, label, value);
}

static int add_variable(Map *symbols, const char *variable_name) {

  int allocated_address = next_variable_address++;
  Map__add(symbols, variable_name, allocated_address);

  return allocated_address;
}

void add_unresolved_symbol(Map *unresolved_symbols, char *label,
                           int instr_index) {

  Map__add(unresolved_symbols, label, instr_index);
}

void add_instruction(Vector *instructions, enum InstructionType type,
                     union InstructionEntry instruction) {

  struct Instruction *instr = malloc(sizeof(struct Instruction));

  instr->type = type;
  instr->instruction = instruction;
  Vector__add(instructions, instr);
}

static void edit_A_instruction(Vector *instructions, int idx, int aValue) {
  struct Instruction *instr = instructions->items[idx];
  instr->instruction.aValue = aValue;
}

void add_diagnostic(Vector *diagnostics, enum DiagnosticType type, int line_num,
                    char *message) {
  struct Diagnostic *diagnos = malloc(sizeof(struct Diagnostic));

  diagnos->type = type;
  diagnos->line = line_num;
  diagnos->message = message;
  Vector__add(diagnostics, diagnos);
};

void resolve_symbols(Map *symbols, Map *unresolved_symbols,
                     Vector *instructions, Vector *diagnostics) {

  for (int i = 0; i < unresolved_symbols->size; i++) {

    int aValue = get_symbol_value(symbols, unresolved_symbols->data[i].key);
    if (aValue == -1) {

      add_variable(symbols, unresolved_symbols->data[i].key);

      const char *key = unresolved_symbols->data[i].key;
      const char *prefix = "variable ";
      size_t msg_len = strlen(prefix) + strlen(key) + 1;
      char *msg = malloc(msg_len);
      if (msg) {
        snprintf(msg, msg_len, "%s%s", prefix, key);
        add_diagnostic(diagnostics, WARNING, 0, msg);
      }
      aValue = next_variable_address - 1;
    }

    edit_A_instruction(instructions, unresolved_symbols->data[i].value, aValue);
  }

  Map__free(unresolved_symbols);
  return;
};