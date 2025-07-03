#include <string.h>

void get_label(const char *source, char *target)
{
    char *start = strstr(source, "(");
    char *end = strstr(source, ")");

    if (start && end && start < end)
    {
        int length = end - start - 1;
        strncpy(target, start + 1, length);
        target[length] = '\0';
    }
}