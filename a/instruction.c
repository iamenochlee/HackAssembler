#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define INSTRUCTION_BITS 16
#define VALUE_BITS 15

void int_to_bin(int n, char *ptr, int start_index, int end_index);

int resolve_A_instruction(int value, char *instruction)
{
    int_to_bin(value, instruction, 1, VALUE_BITS);

    return 0;
}
