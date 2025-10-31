#include "../include/helpers.h"

int get_symbol_value(Map *symbols, const char *label) {
  int res = Map__find(symbols, label);
  return res;
}

int is_valid_dest(Map *dests, char *dest) {
  int res;
  if ((res = Map__find(dests, dest)) >= 0) {
    return 1;
  }

  return 0;
}
int is_valid_comp(Map *comps, char *comp) {

  int res;
  if ((res = Map__find(comps, comp)) >= 0) {
    return 1;
  }

  return 0;
}
int is_valid_jump(Map *jumps, char *jump) {

  int res;
  if ((res = Map__find(jumps, jump)) >= 0) {
    return 1;
  }

  return 0;
}