#include "../include/utils.h"
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int is_empty_line(char *line) {

  if (line[0] == '\0')
    return 1;

  return 0;
}

LineReader create_line_reader(const char *source) {
  LineReader reader = {.source = source, .idx = 0};
  return reader;
}

int get_line(LineReader *reader, char *line, size_t max_line) {
  if (reader == NULL || reader->source == NULL) {
    return 0;
  }

  if (reader->source[reader->idx] == '\0')
    return 0;

  size_t i = 0;
  while (reader->source[reader->idx] != '\0' &&
         reader->source[reader->idx] != '\n' &&
         reader->source[reader->idx] != '\r' && i + 1 < max_line) {
    line[i++] = reader->source[reader->idx++];
  }
  line[i] = '\0';

  // If truncated, skip to end-of-line
  while (reader->source[reader->idx] != '\0' &&
         reader->source[reader->idx] != '\n' &&
         reader->source[reader->idx] != '\r')
    reader->idx++;

  // Consume CRLF or single CR/LF
  if (reader->source[reader->idx] == '\r')
    reader->idx++;
  if (reader->source[reader->idx] == '\n')
    reader->idx++;

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

char *sanitize_line(char *line) {
  if (line == NULL)
    return NULL;

  int len = strlen(line);
  // remove newline/CR at end
  while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
    line[--len] = '\0';
  }

  // cut inline comments starting with //
  char *comment = strstr(line, "//");
  if (comment != NULL) {
    *comment = '\0';
    len = (int)strlen(line);
  }

  char *line_no_whitespace = remove_whitespace(line);
  return line_no_whitespace;
}