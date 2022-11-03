#include <stdio.h>

int find_digit_amount(int number)
{
    int digits = 0;
    do {
        number /= 10;
        digits++;

    } while(number != 0);

    return digits;
}

int main()
{
    printf("Si programa suranda teigiama skaiciu, turinti daugiausiai skaitmenu.\nNoredami baigti seka, iveskite 0 arba neigiama skaiciu.\n");

    int num, most_digits = 0, biggest_number = 0;
    do {
        scanf("%d", &num);

        int digits = find_digit_amount(num);
        if(digits > most_digits)
        {
            most_digits = digits;
            biggest_number = num;
        }

    } while(num > 0);

    printf("Skaicius, turintis daugiausiai skaitmenu: %d", biggest_number);

    return 0;
}
