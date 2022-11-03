#include <stdio.h>

int main()
{

    printf("Si programa apskaiciuoja n realiuju skaiciu suma, vidurki ir suranda didziausia bei maziausia sekos nari.\nn = ");
    int n;
    double num, max, min, sum = 0;

    scanf("%d", &n);
    if(n < 0) {printf("n negali buti mazesnis uz nuli!"); return -1;}
        else if(n == 0) return 0;

    printf("n1 = ");
    scanf("%lf", &num);
    max = num; min = num;

    int i = 1;
    loop:
        if(i == n) goto end;
        printf("n%d = ", i + 1);
        scanf("%lf", &num);
        sum += num;

        if(num > max) max = num;
            else if(num < min) min = num;

        ++i;

        if(i < n) goto loop;

    end:

    printf("Suma: %.2lf\nVidurkis: %.2lf\nDidziausias: %.2lf\nMaziausias: %.2lf", sum, sum / n, max, min);

    return 0;
}
