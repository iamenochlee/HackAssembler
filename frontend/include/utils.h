#ifndef UTILS_H
#define UTILS_H

#include "types.h"

// checks
int check_if_comment(char *line);
int check_instruction_type(char *line);
int check_if_label(char *line);
int check_if_A_numeric(char *line);

// getters
int get_label(const char *source, char *target);
struct CInstruction parse_c_instruction(const char *c_instr);

// lines
char *sanitize_line(char *line);

// todo
int get_line(char *source, char *line, int max_line);
int is_empty_line(char *line);

#endif