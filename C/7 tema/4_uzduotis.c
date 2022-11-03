#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

void generateArray(int data[], int size, int low, int high)
{
    if(low > high || size > ARRAY_SIZE)
        return;

    srand(time(NULL));

    for(int i = 0; i < size; ++i)
        data[i] = low + rand() % (high - low + 1);
}

int main()
{
    int data[ARRAY_SIZE];
    generateArray(data, ARRAY_SIZE, 10, 20);

    for(int i = 0; i < ARRAY_SIZE; ++i)
        printf("%d ", data[i]);


    return 0;
}
