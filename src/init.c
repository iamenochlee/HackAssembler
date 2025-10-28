#include "header.h"

extern LabelArray label_table;
extern IntArray instructions;

// Static lookup tables (these stay the same)
const int comp_count = 28;
struct KeyVal CompTable[comp_count] = {
    // a=0 computations (using A)
    {"0", 42},   // 0101010
    {"1", 63},   // 0111111
    {"-1", 58},  // 0111010
    {"D", 12},   // 0001100
    {"A", 48},   // 0110000
    {"!D", 13},  // 0001101
    {"!A", 49},  // 0110001
    {"-D", 15},  // 0001111
    {"-A", 51},  // 0110011
    {"D+1", 31}, // 0011111
    {"A+1", 55}, // 0110111
    {"D-1", 14}, // 0001110
    {"A-1", 50}, // 0110010
    {"D+A", 2},  // 0000010
    {"D-A", 19}, // 0010011
    {"A-D", 7},  // 0000111
    {"D&A", 0},  // 0000000
    {"D|A", 21}, // 0010101

    // a=1 computations (using M)
    {"M", 112},   // 1110000
    {"!M", 113},  // 1110001
    {"-M", 115},  // 1110011
    {"M+1", 119}, // 1110111
    {"M-1", 114}, // 1110010
    {"D+M", 66},  // 1000010
    {"D-M", 83},  // 1010011
    {"M-D", 71},  // 1000111
    {"D&M", 64},  // 1000000
    {"D|M", 85}   // 1010101
};

const int dest_count = 8;
struct KeyVal DestTable[dest_count] = {
    {"", 0},   // null = 000
    {"M", 1},  // M = 001
    {"D", 2},  // D = 010
    {"MD", 3}, // MD = 011
    {"A", 4},  // A = 100
    {"AM", 5}, // AM = 101
    {"AD", 6}, // AD = 110
    {"AMD", 7} // AMD = 111
};

const int jump_count = 8;
struct KeyVal JumpTable[jump_count] = {
    {"", 0},    // null = 000
    {"JGT", 1}, // JGT = 001
    {"JEQ", 2}, // JEQ = 010
    {"JGE", 3}, // JGE = 011
    {"JLT", 4}, // JLT = 100
    {"JNE", 5}, // JNE = 101
    {"JLE", 6}, // JLE = 110
    {"JMP", 7}  // JMP = 111
};

void __init()
{

    // Initialize dynamic arrays with reasonable starting sizes
    init_int_array(&instructions, INITIAL_SIZE * 2);
    init_label_array(&label_table, INITIAL_SIZE);

    add_dynamic_label(&label_table, "R0", 0);
    add_dynamic_label(&label_table, "R1", 1);
    add_dynamic_label(&label_table, "R2", 2);
    add_dynamic_label(&label_table, "R3", 3);
    add_dynamic_label(&label_table, "R4", 4);
    add_dynamic_label(&label_table, "R5", 5);
    add_dynamic_label(&label_table, "R6", 6);
    add_dynamic_label(&label_table, "R7", 7);
    add_dynamic_label(&label_table, "R8", 8);
    add_dynamic_label(&label_table, "R9", 9);
    add_dynamic_label(&label_table, "R10", 10);
    add_dynamic_label(&label_table, "R11", 11);
    add_dynamic_label(&label_table, "R12", 12);
    add_dynamic_label(&label_table, "R13", 13);
    add_dynamic_label(&label_table, "R14", 14);
    add_dynamic_label(&label_table, "R15", 15);
    add_dynamic_label(&label_table, "SP", 0);
    add_dynamic_label(&label_table, "LCL", 1);
    add_dynamic_label(&label_table, "ARG", 2);
    add_dynamic_label(&label_table, "THIS", 3);
    add_dynamic_label(&label_table, "THAT", 4);
    add_dynamic_label(&label_table, "SCREEN", 16384);
    add_dynamic_label(&label_table, "KBD", 24576);
}