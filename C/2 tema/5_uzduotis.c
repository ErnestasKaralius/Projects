#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double x, y, z;
    printf("Input three numbers:\n");
    scanf("%lf %lf %lf", &x, &y, &z);

    printf("Result 1: %f\nResult 2: %f", x + 4 * y + pow(z, 3), (x + sqrt(y)) * (pow(z, 4) - abs(z) + 46.3));

    return 0;
}
