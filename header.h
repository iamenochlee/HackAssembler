#define MAX_LINE 256
#define INSTRUCTION_BITS 16
#define TWO_MB (2 << 20)

#define READ_FLAGS "r"

struct Label
{
    char *name;
    int value;
};