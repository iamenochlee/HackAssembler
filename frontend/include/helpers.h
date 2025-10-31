#ifndef HELPERS_H
#define HELPERS_H

#include "structures.h"
#include "types.h"

int get_symbol_value(Map *symbols, const char *symbol_name);
int is_valid_dest(Map *, char *dest);
int is_valid_comp(Map *, char *comp);
int is_valid_jump(Map *, char *jump);

// tables
void init_tables(Map *dests, Map *comps, Map *jumps);
void init_symbols(Map *symbols);

void add_symbol(Map *symbols, const char *symbol_name, int value);
void add_unresolved_symbol(Map *unresolved_symbols, char *symbol_name,
                           int instr_index);

void add_diagnostic(Vector *diagnostics, int line_num, char *message);

void add_instruction(Vector *instructions, enum InstructionType type,
                     union InstructionEntry instruction);

void resolve_symbols(Map *symbols, Map *unresolved_symbols,
                     Vector *instructions, Vector *diagnostics);

#endif