int check_if_comment(char *line) {
  if ((line[0] == '/' && line[1] == '/') || (line[0] == '\0')) {
    return 1;
  }
  return 0;
}

int check_if_label(char *line) {
  if (line[0] == '(') {
    return 1;
  }
  return 0;
}

int check_instruction_type(char *line) {
  if (line[0] == '@') {
    return 0;
  }
  return 1;
}

int check_if_A_numeric(char *line) {
  int i = 1;
  while (line[i] != '\0') {
    if ((line[i] < '0') || (line[i] > '9')) {
      return 0;
    }
    i++;
  }
  return 1;
}
