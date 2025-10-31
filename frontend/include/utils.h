// checks
int check_if_comment(char *line);
int check_instruction_type(char *line);
int check_if_label(char *line);
int check_if_A_numeric(char *line);

// getters
int get_label(const char *source, char *target);
void get_dest_comp_jump(char *c_instr, char *dest, char *comp, char *jump);

// lines
char *remove_whitespace(const char *line);
void sanitize_line(char *line);

// todo
int get_line(char *source, char *line, int max_line);
int is_empty_line(char *line);