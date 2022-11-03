#include <stdio.h>

void swap(int* a, int* b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}

int main()
{

    int a = 2, b = 5;

    swap(&a, &b);

    printf("a = %d b = %d", a, b);

    return 0;
}
