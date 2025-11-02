#include "../include/helpers.h"
#include "../include/structures.h"

inline void init_tables(Map *dests, Map *comps, Map *jumps) {
  // dests
  Map__add(dests, "", 0);
  Map__add(dests, "M", 1);
  Map__add(dests, "D", 2);
  Map__add(dests, "MD", 3);
  Map__add(dests, "A", 4);
  Map__add(dests, "AM", 5);
  Map__add(dests, "AD", 6);
  Map__add(dests, "AMD", 7);

  // jumps
  Map__add(jumps, "", 0);
  Map__add(jumps, "JGT", 1);
  Map__add(jumps, "JEQ", 2);
  Map__add(jumps, "JGE", 3);
  Map__add(jumps, "JLT", 4);
  Map__add(jumps, "JNE", 5);
  Map__add(jumps, "JLE", 6);
  Map__add(jumps, "JMP", 7);

  // comps
  Map__add(comps, "0", 42);
  Map__add(comps, "1", 63);
  Map__add(comps, "-1", 58);
  Map__add(comps, "D", 12);
  Map__add(comps, "A", 48);
  Map__add(comps, "!D", 13);
  Map__add(comps, "!A", 49);
  Map__add(comps, "-D", 15);
  Map__add(comps, "-A", 51);
  Map__add(comps, "D+1", 31);
  Map__add(comps, "A+1", 55);
  Map__add(comps, "D-1", 14);
  Map__add(comps, "A-1", 50);
  Map__add(comps, "D+A", 2);
  Map__add(comps, "D-A", 19);
  Map__add(comps, "A-D", 7);
  Map__add(comps, "D&A", 0);
  Map__add(comps, "D|A", 21);
  Map__add(comps, "M", 112);
  Map__add(comps, "!M", 113);
  Map__add(comps, "-M", 115);
  Map__add(comps, "M+1", 119);
  Map__add(comps, "M-1", 114);
  Map__add(comps, "D+M", 66);
  Map__add(comps, "D-M", 83);
  Map__add(comps, "M-D", 71);
  Map__add(comps, "D&M", 64);
  Map__add(comps, "D|M", 85);
}

inline void init_symbols(Map *symbols) {
  add_symbol(symbols, "R0", 0);
  add_symbol(symbols, "R1", 1);
  add_symbol(symbols, "R2", 2);
  add_symbol(symbols, "R3", 3);
  add_symbol(symbols, "R4", 4);
  add_symbol(symbols, "R5", 5);
  add_symbol(symbols, "R6", 6);
  add_symbol(symbols, "R7", 7);
  add_symbol(symbols, "R8", 8);
  add_symbol(symbols, "R9", 9);
  add_symbol(symbols, "R10", 10);
  add_symbol(symbols, "R11", 11);
  add_symbol(symbols, "R12", 12);
  add_symbol(symbols, "R13", 13);
  add_symbol(symbols, "R14", 14);
  add_symbol(symbols, "R15", 15);
  add_symbol(symbols, "SP", 0);
  add_symbol(symbols, "LCL", 1);
  add_symbol(symbols, "ARG", 2);
  add_symbol(symbols, "THIS", 3);
  add_symbol(symbols, "THAT", 4);
  add_symbol(symbols, "SCREEN", 16384);
  add_symbol(symbols, "KBD", 24576);
}