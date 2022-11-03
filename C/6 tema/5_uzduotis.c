#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 256

int email_is_valid(char email[])
{
    scanf("%[A-Za-z0-9.@]255s", email);

    if(getchar() != '\n')
    {
        printf("El. pastas gali tureti tik raides (a-z), skaicius (0-9) ir taskus (.)!");
        scanf("%*[^\n]255s");
        scanf("%*c");

        return 0;
    }

    int length = strlen(email);

    // Ex. @name or .name
    if(email[0] == '@' || email[0] == '.')
    {
        printf("%c simbolis negali buti el. pasto pradzioje! Tinka tik raides (a-z) ir skaiciai (0-9).\n", email[0]);
        return 0;
    }

    // Ex. .com. or .com@
    if(email[length - 1] == '@' || email[length - 1] == '.')
    {
        printf("%c simbolis negali buti el. pasto gale!\n", email[length - 1]);
        return 0;
    }

    int at_count = 0;
    int dot_count = 0;
    for(int i = 0; i < length; ++i)
    {
        if(email[i] == '@')
        {
            // Ex. @gmail.@com
            ++at_count;
            if(at_count > 1)
            {
                printf("@ simbolis gali kartotis tik viena karta!\n");
                return 0;
            }
            // Ex. name.@
            if(i != 0 && email[i - 1] == '.')
            {
                printf("Naudotojo vardo paskutinis simbolis gali buti tik raides (a-z) ir skaiciai (0-9)!\n");
                return 0;
            }

            // Ex. name@.gmail
            if(i != length - 1 && email[i + 1] == '.')
            {
                printf("Po @ simbolio turi buti bent viena raide (a-z) arba skaicius (0-9)\n");
                return 0;
            }
        }

        if(at_count == 1)
        {
            if(email[i] == '.')
            {
                ++dot_count;
                if(dot_count > 1)
                {
                    printf("Po @ simbolio gali buti tik vienas taskas!\n");
                    return 0;
                }
            }

            // Ex. @5g5.c4m
            else if(email[i] >= '0' && email[i] <= '9')
            {
                printf("Po @ negali buti skaiciu (0-9), tik raides (a-z) ir taskas!\n");
                return 0;
            }
        }
    }

    if(at_count == 0)
    {
        printf("El. paste turi buti @ simbolis!\n");
        return 0;
    }

    if(dot_count == 0)
    {
        printf("Po @ simbolio turi buti taskas!\n");
        return 0;
    }

    return 1;
}

int main()
{
    printf("Si programa patikrina, ar ivestas el. pasto adresas yra teisingai ivestas. Jei taip, jis yra irasomas duomenu bazeje.\nIveskite el. pasto adresa: ");

    char email[MAX_LENGTH];
    while(!email_is_valid(email))
        printf("Is naujo iveskite el pasto adresa: ");

    printf("El. pastas teisingas.\n");

    FILE* email_data = fopen("emails.txt", "a");
    if(email_data == NULL)
    {
        printf("Nepavyko pasiekti duomenu bazes!\n");
        return 0;
    }

    fprintf(email_data, "%s\n", email);
    puts(email + (strchr(email, '@') - email + 1));

    printf("El. pastas sekmingai irasytas i duomenu baze.\n");

    fclose(email_data);
    return 0;
}
