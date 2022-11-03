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

int main()
{


    return 0;
}
