#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 256

int get_symbol_count(char string[], char symbol, int start_pos, int end_pos)
{
    if(end_pos > strlen(string) || start_pos < 1)
        return -1;

    int count = 0;
    for(int i = start_pos - 1; i < end_pos; ++i)
        if(string[i] == symbol || symbol == 0)
            ++count;

    return count;
}

int get_symbol_position(char string[], char symbol, int start_pos, int end_pos)
{
    if(end_pos > strlen(string) || start_pos < 1)
        return -1;

    for(int i = start_pos - 1; i < end_pos; ++i)
        if(string[i] == symbol)
            return i + 1;

    return -1;
}

int has_invalid_symbols(char string[], char valid_symbols[])
{
    int length = strlen(string);
    for(int i = 0; i < length; ++i)
    {
        int found = 0;
        for(int j = 0; j < 12; ++j)
            if(valid_symbols[j] == string[i])
                found = 1;

        if(found == 0)
            return 1;
    }

    return 0;
}

int convert_string_to_number(char string[], int start_pos, int end_pos)
{
    if(end_pos > strlen(string) || start_pos < 1)
        return -1;

    char temp_string[MAX_LENGTH];
    for(int i = start_pos - 1; i < end_pos; ++i)
        temp_string[i] = string[i];

    int number;
    sscanf(temp_string, "%d", &number);

    return number;
}

int has_no_errors(char string[], int length, char valid_symbols[])
{
    int comma_position = get_symbol_position(string, ',', 1, length);

    if(has_invalid_symbols(string, valid_symbols))
    {
        printf("Skaicius turi susideti is skaitmenu [0-9] ir tureti viena kableli!\n");
        return 0;
    }

    else if(comma_position == 1)
    {
        printf("Kablelis negali buti skaiciaus pradzioje!\n");
        return 0;
    }

    else if(comma_position == length)
    {
        printf("Kablelis negali buti skaiciaus pabaigoje!\n");
        return 0;
    }

    else if(get_symbol_count(string, ',', 1, length) > 1)
    {
        printf("Gali buti tik vienas kablelis!\n");
        return 0;
    }

    else if(get_symbol_count(string, '0', 1, 1) == 1 && comma_position != 2)
    {
        printf("0 gali buti skaiciaus pradzioje tik pries kableli!\n");
        return 0;
    }

    else if(convert_string_to_number(string, 1, comma_position) > 1000 || convert_string_to_number(string, 1, comma_position) < 10)
    {
        printf("Skaicius turi buti intervale nuo [10; 1000]!\n");
        return 0;
    }

    else if(get_symbol_count(string, 0, comma_position + 1, length) > 3)
    {
        printf("Po kablelio negali buti daugiau uz 3 skaitmenis!\n");
        return 0;
    }

    return 1;
}

int main()
{
    FILE* file;
    char filename[256] = "in.txt";
    char valid_symbols[12] = "1234567890,\0";
    int length;

    printf("Faile %s iveskite realu skaiciu intervale [10; 1000] iki 3 skaitmenu po kablelio. Si programa atspausdins jo ilgi.\nJei norite testi, spustelekite 1: ", filename);
    getchar();
    while(getchar() != '\n')
        ;

    int not_validated = 1;
    while(not_validated)
    {
        file = fopen(filename, "r");

        if(file == NULL)
            printf("Nepavyko atidaryti failo!\n");

        else
        {
            char string[MAX_LENGTH];
            fgets(string, 255, file);

            length = strlen(string);

            if(has_no_errors(string, length, valid_symbols))
                not_validated = 0;

            fclose(file);
        }


        if(not_validated)
        {
            printf("Iveskite kito duomenu failo pavadinima: ");
            scanf("%[^\n]255s", filename);
            while(getchar() != '\n')
                ;
        }
    }

    printf("Duomenys sekmingai nuskaityti.\nSkaiciaus ilgis: %d", length - 1);
    return 0;
}
