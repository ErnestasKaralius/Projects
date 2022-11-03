#include <stdio.h>

int main()
{
    int largest;
    int num1, num2, num3;

    printf("Input three integers:\n");
    scanf("%d%d%d", &num1, &num2, &num3);

    largest = (num1 > num2) ? num1 : num2;
    largest = (num3 > largest) ? num3 : largest;

    printf("Largest integer: %d", largest);

    return 0;
}
