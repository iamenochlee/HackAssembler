#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include <stddef.h>

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

// Line reader operations
LineReader create_line_reader(const char *source);
int get_line(LineReader *reader, char *line, size_t max_line);
int is_empty_line(char *line);

#endif