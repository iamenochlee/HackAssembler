#include "include/assembler.h"
#include "include/types.h"
#include <stdio.h>
#include <stdlib.h>

static char *read_entire_file(const char *path) {
  FILE *f = fopen(path, "rb");
  if (!f)
    return NULL;
  if (fseek(f, 0, SEEK_END) != 0) {
    fclose(f);
    return NULL;
  }
  long sz = ftell(f);
  if (sz < 0) {
    fclose(f);
    return NULL;
  }
  rewind(f);
  char *buf = malloc((size_t)sz + 1);
  if (!buf) {
    fclose(f);
    return NULL;
  }
  size_t n = fread(buf, 1, (size_t)sz, f);
  fclose(f);
  if (n != (size_t)sz) {
    free(buf);
    return NULL;
  }
  buf[sz] = '\0';
  return buf;
}

int main(int argc, const char **args) {

  char *source = read_entire_file(args[1]);
  if (!source) {
    fprintf(stderr, "Failed to read %s\n", args[1]);
    return 1;
  }

  AssemblerResult *res = assemble(source);
  if (!res) {
    fprintf(stderr, "Assemble failed\n");
    free(source);
    return 1;
  }

  int a_count = 0, c_count = 0;
  for (int i = 0; i < res->instructions->count; i++) {
    struct Instruction *instr = res->instructions->items[i];
    if (instr->type == A_INSTR) {
      a_count++;
      printf("A: @%d\n", instr->instruction.aValue);
    } else {
      c_count++;
      struct CInstruction ci = instr->instruction.cInstruction;
      printf("C: dest='%s' comp='%s' jump='%s'\n", ci.dest, ci.comp, ci.jump);
    }
  }

  printf("a-instr: %d, c-instr: %d, total: %d\n", a_count, c_count,
         res->instructions->count);

  // Print diagnostics with colors: red for errors, yellow for warnings
  for (int i = 0; i < res->diagnostics->count; i++) {
    struct Diagnostic *d = res->diagnostics->items[i];
    const char *color =
        d->type == ERROR ? "\x1b[31m" : "\x1b[33m"; // red / yellow
    const char *type_str = d->type == ERROR ? "[ERROR]" : "[WARNING]";
    fprintf(stderr, "%s%s line %d: %s\x1b[0m\n", color, type_str, d->line,
            d->message);
  }

  // TODO: free(res and internals) if you add a destructor; for now just exit.
  free(source);
  return 0;
}
