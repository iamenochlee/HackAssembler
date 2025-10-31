#include <stdio.h>
#include <string.h>

struct ParseArgsResult {
  int success;
  char *output_file;
  char *input_file;
};

// Command line flags (external linkage for global use)
extern int DEBUG_MODE;   // -d flag for debug output
extern int VERBOSE_MODE; // -v flag for verbose output

void print_usage(const char *program_name) {
  fputs("Usage: ", stderr);
  fputs(program_name, stderr);
  fputs(" [-d] [-v] <input.asm> <output.hack>\n", stderr);
  fputs("  -d: Enable debug output for invalid instructions\n", stderr);
  fputs("  -v: Enable verbose output showing all instructions\n", stderr);
}

struct ParseArgsResult parse_arguments(int argc, const char *argv[]) {
  struct ParseArgsResult result = {0};
  result.success = 1;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-d") == 0) {
      DEBUG_MODE = 1;
    } else if (strcmp(argv[i], "-v") == 0) {
      VERBOSE_MODE = 1;
    } else if (argv[i][0] == '-') {
      fprintf(stderr, "Unknown option: %s\n", argv[i]);
      print_usage(argv[0]);
      result.success = 0;
      return result;
    } else if (result.input_file == NULL) {
      result.input_file = argv[i];
    } else if (result.output_file == NULL) {
      result.output_file = argv[i];
    } else {
      fputs("Too many arguments.\n", stderr);
      print_usage(argv[0]);
      result.success = 0;
      return result;
    }
  }

  if (result.input_file == NULL || result.output_file == NULL) {
    print_usage(argv[0]);
    result.success = 0;
  }

  return result;
}
