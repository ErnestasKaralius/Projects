#include <stdio.h>
#include <math.h>

double solve_quadratic(int a, int b, int c, int d, int sign)
{
    return (double)(-b + sign * sqrt(d)) / (2 * a);
}

int main()
{
    int a, b, c;

    printf("Si programa apskaiciuoja kvadratines lygties sprendinius\nIveskite tris sveikus skaicius:\na = ");
    scanf("%d", &a);
	if(a == 0) goto bad_input;
    printf("b = "); scanf("%d", &b);
    printf("c = "); scanf("%d", &c);

    int d = b*b - 4 * a*c;

    if(d > 0) goto two_solutions;
        else if(d == 0) goto one_solution;
            else goto no_solutions;

    bad_input:
        printf("a negali buti lygus 0!");
        return -1;

    two_solutions:
        printf("x1 = %.2f, x2 = %.2f", solve_quadratic(a, b, c, d, 1), solve_quadratic(a, b, c, d, -1));
        return 0;

    one_solution:
        printf("x = %.2f", solve_quadratic(a, b, c, 0, 1));
        return 0;

    no_solutions:
        printf("Diskriminantas %d < 0. Lygtis sprendiniu neturi.", d);

    return 0;
}
