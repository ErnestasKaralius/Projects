#include <stdio.h>

int main()
{
    int num, not_validated = 1;

    printf("Si programa suskaiciuoja ivesto skaiciaus faktoriala.\n");
    while(not_validated)
    {
        printf("Iveskite teigiama skaiciu: ");
        if(scanf("%d", &num) != 1 || getchar() != '\n')
        {
            printf("Galite ivesti tik sveika skaiciu!\n");
            scanf("%*[^\n]");
        }
        else if(num < 1)
            printf("Skaicius turi buti teigiamas!\n");
        else
        {
            printf("Duomenys sekmingai nuskaityti.");
            not_validated = 0;
        }
    }

    // Calculating factorial
    for(int i = num - 1; i > 0; --i)
        num *= i;

    // Writing to file
    FILE* output = fopen("out.txt", "w");

    if(output == NULL)
    {
        printf("\nIvyko klaida rasant i faila!");
        return 0;
    }

    printf("\nRezultatas irasytas i faila.");

    printf("\nFaktorialas: %d", num);
    fprintf(output, "Faktorialas: %d", num);

    fclose(output);
    return 0;
}
