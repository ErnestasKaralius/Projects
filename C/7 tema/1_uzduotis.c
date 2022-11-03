#include <stdio.h>

int isInRange(int number, int low, int high)
{
    if(low <= high && number >= low && number <= high)
        return 1;

    return 0;
}

int main()
{
    int low, high, number;
    printf("Iveskite intervala [a; b]: ");
    scanf("%d%d", &low, &high);

    printf("Iveskite skaiciu: ");
    scanf("%d", &number);

    printf("%d %s intervale [%d; %d]", number, isInRange(number, low, high) ? "yra" : "nera", low, high);

    return 0;
}
