#include <stdio.h>

int main()
{
    int a, b, c;

    printf("Si programa atspausdins teigiamus sveikus skaicius is intervalo (a; b], kurie dalinasi is c su liekana 1.\nIveskite tris sveikus skaicius:\n");

    printf("a = "); scanf("%d", &a);
    printf("b = "); scanf("%d", &b);
    if(b < a) {printf("b negali buti mazesnis uz a!"); return -1;}
    printf("c = "); scanf("%d", &c);

    loop:
        ++a;
        if(a > 0 && a % c == 1 && a <= b)
            printf("%d ", a);

        if(a < b) goto loop;

    return 0;
}
