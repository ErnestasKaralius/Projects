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
    int digit_seperator = power_of(10, sorted_digits - 1);
    for(int i=1; i<=sorted_digits; i++)
    {
        int sorted_digit = sorted_number / digit_seperator;
        if(digit <= sorted_digit) return i;

        sorted_number %= digit_seperator;
        digit_seperator /= 10;
    }

    return sorted_digits;
}

int sort_number(int digit, int sorted_number, int sorted_digits, int position)
{
    int temp_number = sorted_number, temp_digit_amount = sorted_digits;
    int new_sorted;

    // If it's the last digit
    if(position == sorted_digits && digit > sorted_number % 10) {new_sorted = digit; position++;}
    else new_sorted = digit * power_of(10, sorted_digits + 1 - position);

    int digit_seperator = power_of(10, sorted_digits - 1);
    // Loop through sorted number
    for(int j=1; j<=sorted_digits; j++)
    {
        int enlarger = (j < position) ? sorted_digits - j + 1 : sorted_digits - j; // Enlarge the number. By 10 if on the left of i, otherwise not
        new_sorted += temp_number / digit_seperator * power_of(10, enlarger);

        temp_number %= digit_seperator;
        digit_seperator /= 10;
    }

    return new_sorted;
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
            sorted_number = sort_number(digit, sorted_number, sorted_digits, find_insert_position(digit, sorted_number, sorted_digits));
            sorted_digits++;

            number %= digit_seperator;
            digit_seperator /= 10;
        }

        printf("Sorted number: %d\n", sorted_number);
    }

    return 0;
}
