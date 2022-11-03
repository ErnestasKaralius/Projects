#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* createArray(int size, int low, int high)
{
    if(low > high)
        return NULL;

    srand(time(NULL));

    int* array = malloc(size * sizeof(int));
    if(array == NULL)
        return NULL;

    for(int i = 0; i < size; ++i)
        *(array + i) = low + rand() % (high - low + 1);

    return array;
}

int main()
{
    int* array = createArray(10, 5, 10);

    free(array);
    return 0;
}
