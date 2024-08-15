#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

long get_file_size(FILE *file);
int get_line(char line[], int MAXLINE, char *buf);

long get_file_size(FILE *file)
{
    if (fseek(file, 0, SEEK_END) != 0)
        exit(2);

    long size = ftell(file);
    rewind(file);

    return size;
}