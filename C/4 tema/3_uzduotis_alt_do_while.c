#include <stdio.h>

int main()
{
	int a, b, c;
	printf("Si programa suranda c-aji sekos skaiciu.\nIveskite tris neneigiamus sveikus skaicius:\na = ");

    scanf("%d", &a);
    printf("b = "); scanf("%d", &b);
    printf("c = "); scanf("%d", &c);

	if(a < 0 || b < 0 || c < 0) {printf("Argumentai negali buti neigiami!"); return -1;}

	int f0 = a, f1 = b, sum = 0, i = 0;

	do {
        if(c == 0) break;
        sum = f1 + f0;
        f0 = f1;
        f1 = sum;

        ++i;
    } while(i < c);

	printf("\n%d-asis skaicius: %d", c, sum);

	return 0;
}
