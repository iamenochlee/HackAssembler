#include "../header.h"

extern struct Label LabelTable[];
extern int label_count;

void add_label(char *lname, int lvalue)
{
    LabelTable[label_count].name = malloc(strlen(lname) + 1);
    strcpy(LabelTable[label_count].name, lname);
    LabelTable[label_count].value = lvalue;
    label_count++;
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
