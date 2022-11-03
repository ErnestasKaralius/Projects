#include <stdio.h>

// Because C hates me
int power_of(int x, int y)
{
    if(y == 0) return 1;

    int number = x;
    for(int i=2; i<=y; i++)
        number *= x;

    return number;
}

int get_digit_amount(int number)
{
    int digits = 1;
    while(number != 0)
    {
        number /= 10;
        if(number != 0) digits++;
    }

    return digits;
}

int find_insert_position(int digit, int sorted_number, int sorted_digits)
{
    // Get digits from Left to Right
    int divider = power_of(10, sorted_digits - 1);
    for(int i=1; i<=sorted_digits; i++)
    {
        int sorted_digit = sorted_number / divider;
        if(digit >= sorted_digit) return i;

        sorted_number %= divider;
        divider /= 10;
    }

    return sorted_digits + 1;
}

int sort_number(int sorted_number, int sorted_digits, int digit, int position)
{
    int new_number = new_number = digit * power_of(10, sorted_digits - position + 1);
    int divider = power_of(10, sorted_digits - 1);
    for(int i=1; i<=sorted_digits; i++)
    {
        int temp_digit = sorted_number / divider;
        if(i < position) new_number += temp_digit * divider * 10; // Digits to the Left increased by 10
            else new_number += temp_digit * divider; // Digits to the Right remain same

        sorted_number %= divider;
        divider /= 10;
    }
    return new_number;
}

int main()
{
    while(1)
    {
        int sorted_number = 0, sorted_digits = 0;
        int number;

        printf("Input number to sort: ");
        if(scanf("%d", &number) != 1 || getchar() != '\n')
        {
            printf("Input only integers!\n");
            while(getchar() != '\n') ; // Get input until the end to avoid errors
            continue;
        }
        else if(number < 0) {printf("Input non-negative integers!\n"); continue;}

        int digits = get_digit_amount(number);
        int digit_seperator = power_of(10, digits - 1); // We use this to get the digits from left to right

        // Loop through the given number
        for(int i=1; i<=digits; i++)
        {
            int digit = number / digit_seperator;
            sorted_number = sort_number(sorted_number, sorted_digits, digit, find_insert_position(digit, sorted_number, sorted_digits));
            sorted_digits++;

            number %= digit_seperator;
            digit_seperator /= 10;
        }

        printf("Sorted number: %d\n", sorted_number);
    }

    return 0;
}
