#include "header.h"

IntArray instructions;
LabelArray label_table;
extern struct KeyVal CompTable, JumpTable, DestTable;
extern int comp_count, jump_count, dest_count;

int next_variable_address = 16; // Start variable allocation at address 16

// Command line flags
int DEBUG_MODE = 0;   // -d flag for debug output
int VERBOSE_MODE = 0; // -v flag for verbose output

int main(int argc, char *argv[])
{
  char *input_file = NULL;
  char *output_file = NULL;

  // Parse command line arguments
  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-d") == 0)
    {
      DEBUG_MODE = 1;
    }
    else if (strcmp(argv[i], "-v") == 0)
    {
      VERBOSE_MODE = 1;
    }
    else if (argv[i][0] == '-')
    {
      fprintf(stderr, "Unknown option: %s\n", argv[i]);
      fputs("Usage: ./prog [-d] [-v] <input.asm> <output.hack>\n", stderr);
      fputs("  -d: Enable debug output for invalid instructions\n", stderr);
      fputs("  -v: Enable verbose output showing all instructions\n", stderr);
      return 1;
    }
    else if (input_file == NULL)
    {
      input_file = argv[i];
    }
    else if (output_file == NULL)
    {
      output_file = argv[i];
    }
    else
    {
      fputs("Too many arguments.\n", stderr);
      fputs("Usage: ./prog [-d] [-v] <input.asm> <output.hack>\n", stderr);
      return 1;
    }
  }

  if (input_file == NULL || output_file == NULL)
  {
    fputs("Usage: ./prog [-d] [-v] <input.asm> <output.hack>\n", stderr);
    fputs("  -d: Enable debug output for invalid instructions\n", stderr);
    fputs("  -v: Enable verbose output showing all instructions\n", stderr);
    return 1;
  }

  __init();
  FILE *file = open_file(input_file);
  __setup(file);

  int output_size = instructions.size * 17;
  char *buffer = malloc(output_size);
  if (buffer == NULL)
  {
    fprintf(stderr, "Error: Failed to allocate output buffer of size %d\n", output_size);
    fclose(file);
    return 1;
  }

  printf("Compiling %d instructions, allocated %d bytes for output\n", instructions.size, output_size);
  compile(file, buffer);

  FILE *outfile = fopen(output_file, WRITE_FLAGS);
  if (outfile == NULL)
  {
    perror("Failed to open output file");
    free(buffer);
    fclose(file);
    return 1;
  }
  fputs(buffer, outfile);
  fclose(outfile);

  printf("Compiled Successfully!\n");

  free(buffer);
  fclose(file);

  // Cleanup
  free_int_array(&instructions);
  free_label_array(&label_table);

  return 0;
}

void compile(FILE *file, char *buffer)
{

  buffer[0] = '\0';
  int buffer_pos = 0;
  int buffer_size = instructions.size * 17 + 1;

  for (int i = 0; i < instructions.size; i++)
  {
    int current_line = 0;
    rewind(file);
    char line[MAX_LINE];
    get_line_by_number_sequential(file, line, sizeof(line), instructions.data[i], &current_line);
    strip_line_endings(line); // Remove \r and \n
    char *line_no_whitespace = remove_whitespace(line);

    // Remove inline comment from line_no_whitespace
    char *comment_start = strstr(line_no_whitespace, "//");
    if (comment_start != NULL)
    {
      *comment_start = '\0';
    }

    if (VERBOSE_MODE)
    {
      printf("Instruction %d (line %d): %s\n", i + 1, instructions.data[i] + 1, line_no_whitespace);
    }

    if (get_instruction_type(line_no_whitespace))
    {
      // c instruction: dest=comp;jump
      // pick dest, or null when empty, max 3rd char is =
      char *dest = malloc(4);
      dest[0] = '\0'; // Initialize as empty string
      int dest_in = 1;
      int dest_found = 0;

      while (dest_in < 4)
      {
        dest_in++;
        if (line_no_whitespace[dest_in - 1] == '=')
        {
          dest_found = 1; // Set the existing variable, don't declare new one
          break;
        }
      }

      if (dest_found)
      {
        strncpy(dest, line_no_whitespace, dest_in - 1);
        dest[dest_in - 1] = '\0'; // Null terminate
      }

      // pick comp, check up to ;, if no = all is comp
      char *comp = malloc(4);
      comp[0] = '\0';                            // Initialize as empty string
      int comp_start = dest_found ? dest_in : 0; // Start after '=' or from beginning
      int comp_len = 0;

      while (line_no_whitespace[comp_start] != '\0' && line_no_whitespace[comp_start] != ';' && comp_len < 3)
      {
        comp[comp_len] = line_no_whitespace[comp_start];
        comp_len++;
        comp_start++;
      }
      comp[comp_len] = '\0';

      // pick jump after ;
      char *jump = malloc(4); // Max jump length
      jump[0] = '\0';         // Initialize as empty string
      if (line_no_whitespace[comp_start] == ';')
      {
        strcpy(jump, line_no_whitespace + comp_start + 1); // Copy after ';'
      }

      // Generate C-instruction binary
      int comp_value = get_Value(&CompTable, comp_count, comp);
      int dest_value = get_Value(&DestTable, dest_count, dest);
      int jump_value = get_Value(&JumpTable, jump_count, jump);

      if (comp_value != -1 && dest_value != -1 && jump_value != -1)
      {
        char output[] = "1110000000000000";

        // Set a-bit (bit 3) if comp uses M
        if (strchr(comp, 'M') != NULL)
        {
          output[3] = '1';
        }

        int_to_bin(comp_value, output, 4, 9);
        int_to_bin(dest_value, output, 10, 12);
        int_to_bin(jump_value, output, 13, 15);

        // Append to buffer
        if (buffer_pos + 17 >= buffer_size)
        {
          fprintf(stderr, "Error: Buffer overflow at instruction %d\n", i + 1);
          exit(EXIT_FAILURE);
        }
        strcpy(buffer + buffer_pos, output);
        buffer_pos += INSTRUCTION_BITS; // Move position by 16 characters
        strcpy(buffer + buffer_pos, "\n");
        buffer_pos += 1; // Move position by 1 for newline
      }
      else
      {
        if (DEBUG_MODE || VERBOSE_MODE)
        {
          fprintf(stderr, "Debug: dest='%s', comp='%s', jump='%s'\n", dest, comp, jump);
        }
        fprintf(stderr, "Error: Invalid C-instruction at line %d\n'%s'\n", instructions.data[i] + 1, line_no_whitespace);
        exit(EXIT_FAILURE);
      }

      free(dest);
      free(comp);
      free(jump);
    }
    else
    {
      // a instruction
      char output[] = "0000000000000000";

      if (check_if_A_numeric(line_no_whitespace))
      {
        int_to_bin(atoi(line_no_whitespace + 1), output, 1, 15);
      }
      else if (check_if_known_label(line_no_whitespace + 1))
      {
        int value = get_Value(label_table.data, label_table.size, line_no_whitespace + 1);
        int_to_bin(value, output, 1, 15);
      }
      else
      {
        // Check if this is a variable that needs to be allocated
        char *symbol = line_no_whitespace + 1;
        int allocated_address = allocate_variable(symbol);
        int_to_bin(allocated_address, output, 1, 15);
      }

      output[16] = '\0';

      // Append to buffer
      if (buffer_pos + 17 >= buffer_size)
      {
        fprintf(stderr, "Error: Buffer overflow at instruction %d\n", i + 1);
        exit(EXIT_FAILURE);
      }
      strcpy(buffer + buffer_pos, output);
      buffer_pos += INSTRUCTION_BITS;
      strcpy(buffer + buffer_pos, "\n");
      buffer_pos += 1;
    }

    free(line_no_whitespace);
  }

  buffer[buffer_pos] = '\0';
}

void __setup(FILE *file)
{

  int ln = 0;
  int pc = 0;

  char line[MAX_LINE];
  while (get_line(file, line, sizeof(line)))
  {
    strip_line_endings(line); // Remove \r and \n
    char *line_no_whitespace = remove_whitespace(line);

    if (check_if_comment(line_no_whitespace))
    {
      free(line_no_whitespace);
      ln++;
      continue;
    }

    if (check_if_label(line_no_whitespace))
    {
      char *target = malloc(MAX_LINE);
      if (get_label(line_no_whitespace, target))
      {
        fprintf(stderr, "Error: Invalid label declaration'%s' at line %d\n", line_no_whitespace, ln + 1);
        free(target);
        free(line_no_whitespace);
        exit(EXIT_FAILURE);
      }
      add_dynamic_label(&label_table, target, pc);
      free(target);
      free(line_no_whitespace);
      ln++;
      continue;
    }

    else
    {
      add_instruction(&instructions, ln);
    }

    pc++;
    free(line_no_whitespace);
    ln++;
  }
}
