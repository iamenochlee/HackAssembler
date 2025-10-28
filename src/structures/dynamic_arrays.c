#include "../header.h"

extern int VERBOSE_MODE;

void init_int_array(IntArray *arr, int initial_capacity)
{
    arr->data = malloc(sizeof(int) * initial_capacity);
    if (arr->data == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate initial array capacity\n");
        exit(EXIT_FAILURE);
    }
    arr->size = 0;
    arr->capacity = initial_capacity;

    if (VERBOSE_MODE)
    {
        printf("Initialized instruction array with capacity %d\n", initial_capacity);
    }
}

void init_label_array(LabelArray *arr, int initial_capacity)
{
    arr->data = malloc(sizeof(struct KeyVal) * initial_capacity);
    if (arr->data == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate initial label array capacity\n");
        exit(EXIT_FAILURE);
    }
    arr->size = 0;
    arr->capacity = initial_capacity;

    if (VERBOSE_MODE)
    {
        printf("Initialized label array with capacity %d\n", initial_capacity);
    }
}

static void grow_int_array(IntArray *arr)
{
    int old_capacity = arr->capacity;
    arr->capacity *= 2; // Double the size (exponential growth)

    arr->data = realloc(arr->data, sizeof(int) * arr->capacity);
    if (arr->data == NULL)
    {
        fprintf(stderr, "Error: Failed to grow instruction array to capacity %d\n", arr->capacity);
        exit(EXIT_FAILURE);
    }

    if (VERBOSE_MODE)
    {
        printf("Grew instruction array from %d to %d capacity (reallocation occurred)\n",
               old_capacity, arr->capacity);
    }
}

static void grow_label_array(LabelArray *arr)
{
    int old_capacity = arr->capacity;
    arr->capacity *= 2; // Double the size (exponential growth)

    arr->data = realloc(arr->data, sizeof(struct KeyVal) * arr->capacity);
    if (arr->data == NULL)
    {
        fprintf(stderr, "Error: Failed to grow label array to capacity %d\n", arr->capacity);
        exit(EXIT_FAILURE);
    }

    if (VERBOSE_MODE)
    {
        printf("Grew label array from %d to %d capacity (reallocation occurred)\n",
               old_capacity, arr->capacity);
    }
}

void add_instruction(IntArray *arr, int line_num)
{
    if (arr->size >= arr->capacity)
    {
        grow_int_array(arr);
    }

    arr->data[arr->size] = line_num;
    arr->size++;
}

void add_dynamic_label(LabelArray *arr, const char *name, int value)
{
    if (arr->size >= arr->capacity)
    {
        grow_label_array(arr);
    }

    arr->data[arr->size].key = malloc(strlen(name) + 1);
    if (arr->data[arr->size].key == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate memory for label name '%s'\n", name);
        exit(EXIT_FAILURE);
    }

    strcpy(arr->data[arr->size].key, name);
    arr->data[arr->size].value = value;
    arr->size++;
}

void free_int_array(IntArray *arr)
{
    if (arr->data != NULL)
    {
        free(arr->data);
        arr->data = NULL;
    }
    arr->size = 0;
    arr->capacity = 0;
}

void free_label_array(LabelArray *arr)
{
    if (arr->data != NULL)
    {
        // Free individual label names
        for (int i = 0; i < arr->size; i++)
        {
            if (arr->data[i].key != NULL)
            {
                free(arr->data[i].key);
            }
        }
        free(arr->data);
        arr->data = NULL;
    }
    arr->size = 0;
    arr->capacity = 0;
}
