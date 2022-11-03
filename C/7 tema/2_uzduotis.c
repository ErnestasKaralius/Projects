#include <stdio.h>

long int getFactorial(int number)
{
    return (number == 0) ? 1 : (number < 0 ) ? 0 : number * getFactorial(number - 1);
}

long int getFactorial2(int number)
{
    if(number == 0)
        return 1;

    else if(number < 0)
        return 0;

    for(int i = number - 1; i > 1; --i)
        number *= i;

    return number;
}


int main()
{
    int number;
    scanf("%d", &number);

    printf("%ld\n%ld", getFactorial(number), getFactorial2(number));

    return 0;
}
