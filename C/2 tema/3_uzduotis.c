#include <stdio.h>

int main()
{
    int number;
    printf("%s", "Iveskite skaiciu: ");
    scanf("%d", &number);

    printf("Skaicius %d %s", number, number % 2 == 0 ? "lyginis" : "nelyginis");

    return 0;
}
