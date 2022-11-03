#include <stdio.h>

long decimal_to_binary(int number)
{
    long binary = 0;
    int multiplier = 1;
    while(number != 0)
    {
        int remainder = number % 2;
        binary += remainder * multiplier;
        multiplier *= 10;
        number /= 2;
    }

    return binary;
}

int main()
{
    printf("Binary to decimal: %d %d %d\n", 0b11011, 0b10010100, 0b11001011010101);
    printf("Decimal to binary: %d %d %d\n", decimal_to_binary(32), decimal_to_binary(241), decimal_to_binary(2487) /* Too big for long */);
    printf("Hex to decimal: %d %d %d\n", 0x6E2, 0xED33, 0x123456);
    printf("Decimal to hex: %X %X %X\n", 243, 2483, 4612);

    return 0;
}
