#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

long get_file_size(FILE *file);
int copy_file(FILE *file, char **copy_to, long size);
int remove_white_spaces(char **copied_file, int size);
int get_line(char line[], int MAXLINE, char *buf);

void parse_file(FILE *file)
{

    long file_size = get_file_size(file);
    char *copied_file = NULL;

    if (copy_file(file, &copied_file, file_size) != 0)
    {
        fprintf(stderr, "Read Error");
        exit(1);
    }

    fclose(file);

    remove_white_spaces(&copied_file, file_size);

    printf("%s\n", copied_file);
}

int copy_file(FILE *file, char **copy_to, long size)
{

    *copy_to = (char *)malloc(size + 1);

    if (!*copy_to)
    {
        perror("Allocation Error:");
        exit(1);
    }

    if (fread(*copy_to, size, 1, file) != 1)
        return 1;

    return 0;
}

int remove_white_spaces(char **copied_file, int size)
{

    char *buf = (char *)malloc(size + 1);
    char line[MAX_LINE];

    int count;
    while ((count = get_line(line, MAX_LINE, *copied_file)) >= 0)
    {
        if (count > 0)
            strcat(buf, line);
    }

    free(*copied_file);

    *copied_file = buf;
}

int remove_comments(char **copied_file, int size)
{

    char *buf = (char *)malloc(size + 1);
    char line[MAX_LINE];

    int count;
    while ((count = get_words_before_comment(line, MAX_LINE, *copied_file)) >= 0)
    {

        printf("%s", line);
    }

    // free(*copied_file);

    // *copied_file = buf;
}

int get_line(char line[], int MAXLINE, char *buf)
{

    static int POS = 0;
    memset(line, 0, MAX_LINE);

    int count;
    for (count = 0; count < MAXLINE; count++, POS++)
    {
        char ch = buf[POS];

        if (ch == '\0')
            return -1;

        if (ch == '\n')
        {
            line[count] = ch;
            POS++;
            break;
        }

        line[count] = ch;
    }

    return count - 1;
}

long get_file_size(FILE *file)
{
    if (fseek(file, 0, SEEK_END) != 0)
        exit(2);

    long size = ftell(file);
    rewind(file);

    return size;
}