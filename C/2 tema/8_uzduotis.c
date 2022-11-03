#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

char hex_digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

int binary_to_decimal(char binary[256])
{
    int number = 0;
    int length = strlen(binary);

    // From left to right 1 * 10^2 + 1 * 10^1 + 1* 10^0
    for(int i=0; i<length; i++)
        if(binary[i] == '1') number += pow(2, length - i - 1);

    return number;
}

char* decimal_to_binary(int number)
{
    char* binary = malloc(256);
    int length = 0;
    if(number == 0) {binary[0] = '0'; length++;}

    while(number != 0)
    {
        int remainder = number % 2;
        number /= 2;
        binary[length] = (remainder == 1) ? '1' : '0';
        length++;
    }

    // Reverse the array
    for(int i=0; i<length/2; i++)
    {
        char temp_digit = binary[i];
        binary[i] = binary[length - i - 1];
        binary[length - i - 1] = temp_digit;
    }

    binary[length] = '\0';
    return binary;
}

int hex_to_decimal(char hex[256])
{
   int number = 0;
   int length = strlen(hex);

   for(int i=0; i<length; i++)
   {
       // Get the number corresponding to a given hex char
       for(int j=0; j<16; j++)
            if(hex_digits[j] == hex[i])
               {number += j * pow(16, length - i - 1); break;} // 3 * 16^2 + 5 * 16^1 + 1 * 16^0
   }

   return number;
}

char* decimal_to_hex(int number)
{
    char* hex = malloc(256);
    int length = 0;
    if(number == 0) {hex[0] = '0'; length++;}

    while(number != 0)
    {
        int remainder = number % 16;
        number /= 16;
        hex[length] = hex_digits[remainder];
        length++;
    }

    // Reverse the array
    for(int i=0; i<length/2; i++)
    {
        char temp_digit = hex[i];
        hex[i] = hex[length - i - 1];
        hex[length - i - 1] = temp_digit;
    }

    hex[length] = '\0';
    return hex;
}

char* hex_to_binary(char hex[256])
{
    char* binary = malloc(256);

    int length = 0;

    for(int i=0; i<strlen(hex); i++)
        for(int j=0; j<16; j++)
            if(hex_digits[j] == hex[i])
            {
                char* digit_binary = decimal_to_binary(j);

                // Every hex digit must have 4 digits of binary representation
                if(strlen(digit_binary) < 4)
                    for(int k=strlen(digit_binary); k < 4; k++) // 11 = 0011
                        {binary[length] = '0'; length++;}

                // Insert converted decimal digits
                for(int k=0; k<strlen(digit_binary); k++)
                    {binary[length] = digit_binary[k]; length++;}

                free(digit_binary);
                break;
            }

    binary[length] = '\0';
    return binary;
}

char* binary_to_hex(char binary[256])
{
    char* hex = malloc(256);

    int length = 0, number = 0;
    int remainder = strlen(binary) % 4;

    if(remainder != 0)
    {
        for(int i=0; i<remainder; i++)
            if(binary[i] == '1') number += pow(2, remainder - i - 1);

        hex[0] = decimal_to_hex(number)[0];
        length++;
        number = 0;
    }

    int position = 0;
    for(int i=remainder; i<strlen(binary); i++)
    {
        if(binary[i] == '1') number += pow(2, 3 - position);
        position++;

        if(position == 4)
        {
            hex[length] = decimal_to_hex(number)[0];
            length++;
            number = 0;
            position = 0;
        }
    }

    hex[length] = '\0';
    return hex;
}

char get_numeral_system(char first_type)
{
    char numeral_system;
    while(1)
    {
        printf("Choose numeral system: ");
        scanf("%c", &numeral_system);
        if(numeral_system != 'b' && numeral_system != 'd' && numeral_system != 'h' || numeral_system == first_type || getchar() != '\n')
        {
            printf("Enter one unique character from list!\n");
            while(getchar() != '\n') ;
            continue;
        }
        return numeral_system;
    }
}

int get_number()
{
    int number;
    while(1)
    {
        printf("Input: ");
        if(scanf("%d", &number) != 1 || getchar() != '\n')
        {
            printf("Enter a number!\n");
            while(getchar() != '\n') ;
            continue;
        }
        return number;
    }
}

char* get_characters(char type)
{
    char* characters = malloc(256);

    while(1)
    {
        printf("Input: ");
        scanf("%s", characters);

        if(type == 'h')
        {
            int is_good = 1;
            for(int i=0; i<strlen(characters); i++)
            {
                int is_valid = 0;
                // Check if digit is in the table
                for(int j=0; j<16; j++)
                    if(characters[i] == hex_digits[j])
                        {is_valid = 1; break;}

                if(!is_valid)
                {
                    is_good = 0;
                    printf("Input valid characters!\n");
                    while(getchar() != '\n') ;
                    break;
                }
            }
            if(is_good) break;
        }
        else
        {
            int is_valid = 1;
            for(int i=0; i<strlen(characters); i++)
                // Must be 1 and 0
                if(characters[i] != '0' && characters[i] != '1')
                {
                    is_valid = 0;
                    printf("Input valid characters!\n");
                    while(getchar() != '\n') ;
                    break;
                }

            if(is_valid) break;
        }
    }
    while(getchar() != '\n') ;
    return characters;
}

int main()
{
    printf("Numeral systems:\n|b - binary\n|d - decimal\n|h - hex\n");
    for(int i=0; i<50; i++) printf("%c", '-');
    printf("%c", '\n');

    while(1)
    {
        int number;
        char* characters = NULL;
        char* output = NULL;
        char type[3];

        type[0] = get_numeral_system('0');

        if(type[0] == 'd') number = get_number();
        else characters = get_characters(type[0]);

        type[1] = get_numeral_system(type[0]);
        type[2] = '\0';

        printf("Result: ");
        if(strcmp(type, "bd") == 0) printf("%d\n", binary_to_decimal(characters));
        else if(strcmp(type, "db") == 0) printf("%s\n", output = decimal_to_binary(number));
        else if(strcmp(type, "hd") == 0) printf("%d\n", hex_to_decimal(characters));
        else if(strcmp(type, "dh") == 0) printf("%s\n", output = decimal_to_hex(number));
        else if(strcmp(type, "hb") == 0) printf("%s\n", output = hex_to_binary(characters));
        else printf("%s\n", output = binary_to_hex(characters));

        for(int i=0; i<50; i++) printf("%c", '-');
        printf("%c", '\n');

        free(output);
        free(characters);
    }

    return 0;
}
