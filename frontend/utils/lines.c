
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int is_empty_line(char *line) {

  if (line[0] == '\0')
    return 1;

  return 0;
}

int get_line(char *source, char *line, size_t max_line) {
  static const char *base = NULL;
  static size_t idx = 0;

  if (source != base) {
    base = source;
    idx = 0;
  }
  if (source[idx] == '\0')
    return 0;

  size_t i = 0;
  while (source[idx] != '\0' && source[idx] != '\n' && source[idx] != '\r' &&
         i + 1 < max_line) {
    line[i++] = source[idx++];
  }
  line[i] = '\0';

  // If truncated, skip to end-of-line
  while (source[idx] != '\0' && source[idx] != '\n' && source[idx] != '\r')
    idx++;

  // Consume CRLF or single CR/LF
  if (source[idx] == '\r')
    idx++;
  if (source[idx] == '\n')
    idx++;

  return 1;
}

char *remove_whitespace(const char *line) {
  if (line == NULL) {
    return NULL;
  }

  // Calculate length needed (excluding whitespace)
  int len = strlen(line);
  int new_len = 0;
  for (int i = 0; i < len; i++) {
    if (!isspace(line[i])) {
      new_len++;
    }
  }

  // Allocate memory for new string
  char *result = malloc(new_len + 1);
  if (result == NULL) {
    return NULL;
  }

  // Copy non-whitespace characters
  int j = 0;
  for (int i = 0; i < len; i++) {
    if (!isspace(line[i])) {
      result[j++] = line[i];
    }
  }
  result[j] = '\0';

  return result;
}

void strip_line_endings(char *line) {
  if (line == NULL)
    return;

  int len = strlen(line);
  while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
    line[--len] = '\0';
  }
}