#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 50

char*** create_string_array(int n, int m)
{
    char*** array = calloc(1, n * sizeof(*array));

    for(int i = 0; i < n; ++i)
    {
        *(array + i) = calloc(1, m * sizeof(**array));

        for(int j = 0; j < m; ++j)
            *(*(array + i) + j) = calloc(1, MAX_STRING_LENGTH);
    }

    return array;
}

void insert_string(char*** array, int i, int j, char* string)
{
    char* ptr = realloc(*(*(array + i) + j), MAX_STRING_LENGTH);
    strcpy(ptr, string);
}

char* get_string(char*** array, int i, int j)
{
    return *(*(array + i) + j);
}

void free_array(char*** array, int n, int m)
{
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
            free(*(*(array + i) + j));

        free(*(array + i));
    }

    free(array);
}


int main()
{
    int n = 10, m = 10;
    char*** array = create_string_array(n, m);

    insert_string(array, 0, 0, "Hello, World!\0");
    printf("%s", get_string(array, 0, 0));
    free_array(array, n, m);

    return 0;
}
