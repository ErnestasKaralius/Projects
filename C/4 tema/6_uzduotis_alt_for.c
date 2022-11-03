#include <stdio.h>

int find_digit_amount(int number)
{
    int digits = 1;
    number /= 10;
    for(number; number != 0; number /= 10)
        digits++;

    return digits;
}

int main()
{
    printf("Si programa suranda teigiama skaiciu, turinti daugiausiai skaitmenu.\nNoredami baigti seka, iveskite 0 arba neigiama skaiciu.\n");

    int num = 1, most_digits = 0, biggest_number = 0;
    for(; num > 0; )
    {
        scanf("%d", &num);

        int digits = find_digit_amount(num);
        if(digits > most_digits)
        {
            most_digits = digits;
            biggest_number = num;
        }
    }

    printf("Skaicius, turintis daugiausiai skaitmenu: %d", biggest_number);

    return 0;
}
