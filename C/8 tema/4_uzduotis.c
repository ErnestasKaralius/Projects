#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE 100

int splitData(char* array, int size, int split_point, char** ptr1, char** ptr2)
{
    if(size < 1 || size > MAX_ARRAY_SIZE || split_point < 0 || split_point > size)
        return -1;

    char* first_array = malloc(split_point);
    if(first_array == NULL)
        return -1;

    char* second_array = malloc(size - split_point);
    if(second_array == NULL)
        return -1;

    for(int i = 0; i < split_point; ++i)
        *(first_array + i) = *(array + i);

    for(int i = 0; i < size - split_point; ++i)
        *(second_array + i) = *(array + i + split_point);

    *ptr1 = first_array;
    *ptr2 = second_array;

    return 0;
}

int main()
{
    char *ptr1, *ptr2;
    char array[MAX_ARRAY_SIZE] = "1234567890\0";

    if(splitData(array, 10, 7, &ptr1, &ptr2) == -1)
        return 0;

    printf("%s\n%s\n", ptr1, ptr2);

    free(ptr1);
    free(ptr2);

    return 0;
}
