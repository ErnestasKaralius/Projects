#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_LENGTH 256

int get_weekday(int day, int month, int year)
{
    if(month <= 2)
    {
      month += 12;
      --year;
    }
    ++month;

    int y = year / 100;
    year %= 100;

    int weekday = day + floor(13 * month / 5) + year + floor(year / 4) + floor(y / 4) + 5 * y;
    weekday %= 7;

    return weekday;
}

int is_leap_year(int year)
{
    if(year % 4 == 0 && year % 100 != 0 && year % 400 != 0)
        return 1;

    return 0;
}

char* get_correct_ending(int days)
{
    if(days % 10 == 1 && days % 100 != 11)
        return "diena";

    if(days % 10 == 0 || days % 100 > 10 && days % 100 < 20)
        return "dienu";

    return "dienas";
}

int date_is_valid(int* weekday)
{
    char date[MAX_LENGTH];
    int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    scanf("%[0-9-]255s", date);
    if(getchar() != '\n')
    {
        printf("Aptikta nagalimu simboliu. Galite ivesti tik skaitmenis ir bruksni!\n");
        scanf("%*[^\n]");
        scanf("%*c");
        return 0;
    }

    /////////////////////////////////
    // Check if dashes are correct //
    /////////////////////////////////

    if(date[0] == '-')
    {
        printf("Bruksnis negali buti datos pradzioje!\n");
        return 0;
    }

    int length = strlen(date);
    int dash_count = 0;

    for(int i = 0; i < length; ++i)
        if(date[i] == '-')
        {
            ++dash_count;
            if(dash_count > 2)
            {
                printf("Tik du bruksniai turi atskirti metus, menesi ir diena! Ivedete %d-iaji (%d pozicija).\n", dash_count, i + 1);
                return 0;
            }

            if(i != length - 1 && date[i + 1] == '-')
            {
                printf("Bruksniai turi skirti metus, menesi ir diena (%d pozicija)!\n", i + 1);
                return 0;
            }
        }

    if(date[length - 1] == '-')
    {
        printf("Bruksnis negali buti datos gale!\n");
        return 0;
    }

    if(dash_count < 2)
    {
        printf("Truksta argumentu. Turi buti metai, menesis ir diena!\n");
        return 0;
    }

    char buff[MAX_LENGTH]; // Temporarily store strings
    int current_pos = 0, delim_pos = 0;

    int numbers[3]; // Store date numbers
    int iteration = 0;

    /////////////////////////////////////////
    // Split the string and perform checks //
    /////////////////////////////////////////

    while(sscanf(date + current_pos, "%[^-]%n", buff, &delim_pos) == 1) // We scan the string, and then continue from last scanned element + 1
    {
        current_pos += delim_pos + 1;

        int number;
        sscanf(buff, "%d", &number);

        numbers[iteration] = number;
        ++iteration;

        // Ex. 020
        if(number > 9 && buff[0] == '0')
        {
            printf("0 gali prasideti tik skaicius, mazesnis uz 10! (%s)\n", buff);
            return 0;
        }

        // Check if month is correct
        if(iteration == 2 && number > 12)
        {
            printf("Menesis negali buti didesnis uz 12! Ivedete %d.\n", number);
            return 0;
        }

        // Check if days are correct
        else if(iteration == 3)
        {
            int year = numbers[0], month = numbers[1];
            int february_leap_yer = 0; // We allow 29 days in February if it's a leap year

            if(month == 2 && is_leap_year(year))
                february_leap_yer = 1;

            int month_days = days_in_month[month - 1];
            if(number > month_days + february_leap_yer)
            {
                printf("Sis menesis turi %d %s. Ivedete %d.\n", month_days, get_correct_ending(month_days), number);
                return 0;
            }
        }
    }

    printf("Duomenys sekmingai nuskaityti.\n");
    *weekday = get_weekday(numbers[2], numbers[1], numbers[0]);

    return 1;
}

int main()
{
    int weekday;
    printf("Si programa atspausdina ivestos datos savaites diena. Iveskite data: ");

    while(1)
    {
        while(!date_is_valid(&weekday))
            printf("Iveskite nauja data: ");

        FILE* weekday_file = fopen("week.txt", "r");
        if(weekday_file == NULL)
        {
            printf("Nepavyko atidaryti savaites dienu (week.txt) failo!");
            return 0;
        }

        char weekday_names[7][256];
        for(int i = 0; i < 7; ++i)
            fscanf(weekday_file, "%s", weekday_names[i]);

        printf("Savaites diena: %s\n", weekday_names[weekday]);

        fclose(weekday_file);

        //////////////////////////
        // Prompt to end program//
        //////////////////////////
        int not_answered = 1;
        while(not_answered)
        {
            printf("Norite testi darba (t/n): ");
            char answer = getchar();
            if(getchar() != '\n')
            {
                scanf("%*[^\n]");
                scanf("%*c");
            }

            else if(answer == 'n')
                return 0;

            else if(answer == 't')
                not_answered = 0;
        }

        printf("Iveskite nauja data: ");
    }

    return 0;
}
