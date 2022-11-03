#include <stdio.h>

int getPositiveNumber(char* msg)
{
    printf("%s", msg);

    int num;
    if(scanf("%d", &num) != 1 || getchar() != '\n')
    {
        scanf("%*[^\n]");
        scanf("%*c");
        getPositiveNumber(msg);
    }
    else
        return num;
}

int main()
{
    printf("%d", getPositiveNumber("Iveskite sveika skaiciu: "));

    return 0;
}
