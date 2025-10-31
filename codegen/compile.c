

// char output[] = "1110000000000000";

// // Set a-bit (bit 3) if comp uses M
// if (strchr(comp, 'M') != NULL) {
//   output[3] = '1';
// }

// int_to_bin(comp_value, output, 4, 9);
// int_to_bin(dest_value, output, 10, 12);
// int_to_bin(jump_value, output, 13, 15);

// // Append to buffer
// if (buffer_pos + 17 >= buffer_size) {
//   fprintf(stderr, "Error: Buffer overflow at instruction %d\n", i + 1);
//   exit(EXIT_FAILURE);
// }
// strcpy(buffer + buffer_pos, output);
// buffer_pos += INSTRUCTION_BITS; // Move position by 16 characters
// strcpy(buffer + buffer_pos, "\n");
// buffer_pos += 1; // Move position by 1 for newline
// }

// else {
//   // a instruction
//   char output[] = "0000000000000000";

//     int_to_bin(value, output, 1, 15);

//     char *symbol = line_no_whitespace + 1;
//     int allocated_address = allocate_variable(symbol);
//     int_to_bin(allocated_address, output, 1, 15);
//   }

//   output[16] = '\0';

//   // Append to buffer
//   if (buffer_pos + 17 >= buffer_size) {
//     fprintf(stderr, "Error: Buffer overflow at instruction %d\n", i + 1);
//     exit(EXIT_FAILURE);
//   }
//   strcpy(buffer + buffer_pos, output);
//   buffer_pos += INSTRUCTION_BITS;
//   strcpy(buffer + buffer_pos, "\n");
//   buffer_pos += 1;

// buffer[buffer_pos] = '\0';
