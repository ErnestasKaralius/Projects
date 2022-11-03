#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 20

int number_is_valid(FILE* file, int* length)
{
    char number[MAX_LENGTH];
    int comma_amount = 0;

    do {
        number[*length] = fgetc(file);

        if(feof(file))
        {
            if(number[*length - 1] == ',')
            {
                printf("Po kabelio turi buti skaitmenys!\n");
                return 0;
            }
            // To give correct number size if a comma exists
            else if(comma_amount == 1)
                --*length;

            number[*length] = '\0';
            break;
        }

        else if(*length >= MAX_LENGTH - 1)
        {
            printf("Pasiekta maksimali skaitmenu riba (%d)!\n", MAX_LENGTH);
            return 0;
        }

        else if(number[*length] == ',')
        {
            ++comma_amount;
            if(length == 0)
            {
                printf("Kablelis negali buti skaiciaus pradzioje!\n");
                return 0;
            }
            else if(*length != 1 && number[0] == '0')
            {
                printf("0 negali buti skaiciaus pradzioje!\n");
                return 0;
            }

            else if(comma_amount > 1)
            {
                printf("Kablelis gali kartotis tik viena karta!\n");
                return 0;
            }
        }

        else if(number[*length] < '0' || number[*length] > '9')
        {
            printf("Aptiktas negalimas simbolis (%c). Galite ivesti tik skaitmenis ir kableli!\n", number[*length]);
            return 0;
        }

        ++*length;

    } while(1);

    char temp_number[MAX_LENGTH];
    int base;

    sscanf(number, "%[^,]", temp_number);
    sscanf(temp_number, "%d", &base);

    if(base < 10 || base > 1000)
    {
        printf("Skaicius turi buti intervale [10; 1000]\n");
        return 0;
    }

    else if(*length - strlen(temp_number) > 3)
    {
        printf("Skaicius gali turete ne daugiau kaip 3 skaitmenis po kablelio!\n");
        return 0;
    }

    return 1;
}

int main()
{
    FILE* file;
    char filename[256] = "in.txt";
    int length = 0; // Length of number

    printf("Faile %s iveskite realu skaiciu intervale [10; 1000] iki 3 skaitmenu po kablelio. Si programa atspausdins jo ilgi.\nJei norite testi, spustelekite 1: ", filename);
    getchar();
    scanf("%*[^\n]");
    scanf("%*c");

    while(1)
    {
        file = fopen(filename, "r");

        if(file == NULL)
            printf("Nepavyko atidaryti failo!\n");

        // Close file if number is not valid
        else if(!number_is_valid(file, &length))
            fclose(file);

        // Entered number is correct
        else
            break;

        printf("Iveskite kito duomenu failo varda: ");
        scanf("%[^\n]255s", filename);
        scanf("%*[^\n]");
        scanf("%*c");
    }

    printf("Duomenys sekmingai nuskaityti.\nSkaiciaus ilgis: %d", length);

    fclose(file);
    return 0;
}
