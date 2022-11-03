#include <stdio.h>

int find_gcd(int a, int b)
{
    int gcd, min = (a < b) ? a : b;

    for(int i = 1; i <= min; ++i)
        if(a % i == 0 && b % i == 0)
            gcd = i;

    return gcd;
}

int find_lcm(int a, int b)
{
    return a * b / find_gcd(a, b);
}

int main()
{
    int a, b, c;
    printf("Si programa suranda triju skaiciu didziausia bendra dalikli ir maziausia bendra kartotini.\nIveskite tris naturalius skaicius:\n");

    scanf("%d%d%d", &a, &b, &c);
    if(a < 1 || b < 1 || c < 1)
    {
        printf("Skaicius negali buti mazesnis arba lygus 0!");
        return -1;
    }

    printf("Didziausias bendras daliklis: %d\nMaziausias bendras kartotinis: %d", find_gcd(a, find_gcd(b, c)), find_lcm(a, find_lcm(b, c)));

    return 0;
}
