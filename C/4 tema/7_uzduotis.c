#include <stdio.h>

int main()
{
    // Signed short
    short number_short = 0;
    short last_short;

    do {
        last_short = number_short;
        ++number_short;
    }
    while(number_short > last_short);


    // Unsigned short
    unsigned short number_unsigned_short = 0;
    unsigned short last_unsigned_short;

    do {
        last_unsigned_short = number_unsigned_short;
        ++number_unsigned_short;
    }
    while(number_unsigned_short > last_unsigned_short);


    // Long
    long number_long = 0;
    long last_long;

    do {
        last_long = number_long;
        ++number_long;
    }
    while(number_long > last_long);


    // Unsigned
    unsigned number_unsigned = 0;
    unsigned last_unsigned;

    do {
        last_unsigned = number_unsigned;
        ++number_unsigned;
    }
    while(number_unsigned > last_unsigned);


    // Unsigned char
    unsigned char number_unsigned_char = 0;
    unsigned char last_unsigned_char;

    do {
        last_unsigned_char = number_unsigned_char;
        ++number_unsigned_char;
    }
    while(number_unsigned_char > last_unsigned_char);


    // Signed char
    char number_signed_char = 0;
    char last_signed_char;

    do {
        last_signed_char = number_signed_char;
        ++number_signed_char;
    }
    while(number_signed_char > last_signed_char);


    printf("short: [%d; %d]\nunsigned short: [%d; %d]\nlong: [%ld; %ld]\nunsigned: [%u; %u]\nunsigned char: [%d; %d]\nsigned char: [%d; %d]",
    number_short, last_short, number_unsigned_short, last_unsigned_short, number_long, last_long, number_unsigned, last_unsigned, number_unsigned_char, last_unsigned_char, number_signed_char, last_signed_char);

    return 0;
}
