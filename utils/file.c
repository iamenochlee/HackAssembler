#include <stdio.h>
#include <stdlib.h>
#include "../header.h"

FILE *open_file(char *filename)
{

    FILE *file = fopen(filename, READ_FLAGS);

    if (file == NULL)
    {
        perror("Error");
        exit(2);
    }

    return file;
}

char *get_line(FILE *file, char *line_buf, int lsize)
{
    return fgets(line_buf, lsize, file);
}

long get_fsize(FILE *file)
{
    long size;

    fseek(file, 0, SEEK_END);
    size = ftell(file);

    fseek(file, 0, SEEK_SET);

    return size;
}

char *get_line_by_number_sequential(FILE *file, char *line_buf, int buf_size, int target_line, int *current_line)
{
    if (file == NULL || line_buf == NULL || current_line == NULL)
        return NULL;

    // If target line is before current position, something's wrong
    if (target_line < *current_line)
        return NULL;

    // If we're already at the target line, just read it
    if (target_line == *current_line)
    {
        if (fgets(line_buf, buf_size, file) != NULL)
        {
            (*current_line)++;
            return line_buf;
        }
        return NULL;
    }

    // Skip lines until we reach target
    char temp_buf[MAX_LINE];
    while (*current_line < target_line)
    {
        if (fgets(temp_buf, sizeof(temp_buf), file) == NULL)
        {
            return NULL; // EOF reached
        }
        (*current_line)++;
    }

    // Now read the target line
    if (fgets(line_buf, buf_size, file) != NULL)
    {
        (*current_line)++;
        return line_buf;
    }

    return NULL;
}