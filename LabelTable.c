#include "header.h"

extern struct Label LabelTable[MAX_LINE];
extern int label_count;
int strcmp();

void add_label(char *lname, int lvalue)
{
    LabelTable[label_count].name = lname;
    LabelTable[label_count].value = lvalue;

    label_count++;
}

int get_lvalue(char *lname)
{
    for (int i = 0; i < label_count; i++)
    {
        if (strcmp(LabelTable[i].name, lname) == 0)
        {
            return LabelTable[i].value;
        }
    }

    return -1;
}