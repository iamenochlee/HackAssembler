#include "../header.h"

extern struct Label LabelTable[];
extern int label_count;
extern int next_variable_address;

void add_label(char *lname, int lvalue)
{
    if (label_count >= MAX_LINE * MAX_LINE)
    {
        fprintf(stderr, "Error: Too many labels. Maximum is %d\n", MAX_LINE * MAX_LINE);
        exit(EXIT_FAILURE);
    }

    LabelTable[label_count].name = malloc(strlen(lname) + 1);
    if (LabelTable[label_count].name == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed for label '%s'\n", lname);
        exit(EXIT_FAILURE);
    }

    strcpy(LabelTable[label_count].name, lname);
    LabelTable[label_count].value = lvalue;
    label_count++;
}

int allocate_variable(char *variable_name)
{
    // Allocate new address for the variable
    int allocated_address = next_variable_address++;
    add_label(variable_name, allocated_address);

    return allocated_address;
}

// todo: better sorting algorithm or structure
int get_lvalue(struct Label table[], int table_count, char *lname)
{
    for (int i = 0; i < table_count; i++)
    { // check for /r
        if (strcmp(table[i].name, lname) == 0)
        {
            return table[i].value;
        }
    }

    return -1;
}
