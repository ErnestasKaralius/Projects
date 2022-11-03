#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 256

int find_middle_number(int a, int b, int c)
{
    if(b > a && a > c || c > a && a > b)
        return a;

    if(a > b && b > c || c > b && b > a)
        return b;

    return c;
}

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

int input_is_correct(int* middle_number)
{
    char string[MAX_LENGTH];
    char valid_symbols[13] = "1234567890;-\0";

    fgets(string, 255, stdin);

    int length = strlen(string);

    if(has_invalid_symbols(string, valid_symbols))
    {
        printf("Ivesti negalimas simbolis! Galite ivesti teigiamus/neigiamus skaicius bei kabliataskius be tarpu!\n");
        return 0;
    }

    else if(get_symbol_count(string, ';', 0, length) > 2)
    {
        printf("Per daug kabliataskiu!\n");
        return 0;
    }


    int semicolons = 0;
    for(int i = 0; i < strlen(string); ++i)
    {
        if(string[i] == ';')
        {
            ++semicolons;
            if(semicolons > 2)
            {
                printf("Per daug kabliataskiu! (%d pozicija)", i + 1);
                return 0;
            }

            if(string[i - 1] < '0' || string[i - 1] > '9')
            {
                if(string[i - 1] == '-')
                {
                    printf("Minusas negali buti skaiciaus gale!");
                    return 0;
                }

                printf("Truksta %d skaiciaus", semicolons);
                return 0;
            }

            if(string[i + 1] != '-' && string[i + 1] < '0' || string[i + 1] > '9')
            {
                printf("Truksta %d skaiciaus", semicolons + 1);
                return 0;
            }
        }
    }


    int arguments = 0;
    int numbers[3];

    char* number = strtok(string, ";");
    while(number != NULL)
    {
        char* end_line = strchr(number, '\n');
        if(end_line)
            *end_line = '\0';

        ++arguments;
        int length = strlen(number);

        for(int i = 1; i < length - 1; ++i)
            if(number[i] == '-')
            {
                printf("Minusas negali buti tarp skaitmenu! (%s)", number);
                return 0;
            }

        if(arguments > 3)
        {
            printf("Galima ivesti tik tris skaicius. Ivedete %d", arguments);
            return 0;
        }

        sscanf(number, "%d", &numbers[arguments - 1]);
        number = strtok(NULL, ";");
    }

    if(arguments < 3)
    {
        printf("Per mazai skaiciu! Ivedete %d", arguments);
        return 0;
    }

    *middle_number = find_middle_number(numbers[0], numbers[1], numbers[2]);

    return 1;
}

int main()
{
    int middle_number;
    printf("Si programa randa vidurini skaiciu. Iveskite 3 teigiamus/neigiamus skaicius, atskirtus kabliataskiais: ");

    while(!input_is_correct(&middle_number))
        printf("\nIs naujo iveskite skaicius: ");

    while(1)
    {
        char filename[MAX_LENGTH];

        printf("\nIveskite isvesties failo varda: ");
        scanf("%[^\n]255s", filename);
        scanf("%*[^\n]");
        scanf("%*c");

        char* dot = strrchr(filename, '.');
        if(dot != NULL && strcmp(dot, ".txt") == 0)
        {
            FILE* output_file = fopen(filename + '\0', "w");
            if(output_file != NULL)
            {
                fprintf(output_file, "%d", middle_number);
                fclose(output_file);
                break;
            }
            printf("\nIvyko klaida rasant i faila!");
        }
        else
            printf("\nFailo gale turi buti nurodytas .txt tipas!");
    }

    return 0;
}
