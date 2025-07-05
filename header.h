#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE 256
#define INSTRUCTION_BITS 16

#define READ_FLAGS "r"
#define WRITE_FLAGS "w"

struct Label
{
    char *name;
    int value;
};

// file
FILE *open_file(char *filename);
long get_fsize(FILE *file);
char *get_line(FILE *file, char *line_buf, int lsize);
char *get_line_by_number_sequential(FILE *file, char *line_buf, int buf_size, int target_line, int *current_line);

// main
void __init(FILE *);
void compile(FILE *file, char *buffer);

// helpers
char *remove_whitespace(const char *line);
void strip_line_endings(char *line);
void copy_instr_to_buf(int startbytes, char *instr_line, char *buf);
void int_to_bin(int n, char *ptr, int start_index, int end_index);

// checks
int check_if_comment(char *line);
int check_if_label(char *line);
int check_if_A_numeric(char *line);
int check_if_known_label(char *label);
int get_instruction_type(char *line);

// label
void add_label(char *lname, int lvalue);
void get_label(const char *source, char *target);
int allocate_variable(char *variable_name);

// lookup table
int get_lvalue(struct Label table[], int table_count, char *lname);
