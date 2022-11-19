#include <assert.h>
#include <stdio.h>

char* my_strcpy(char* dest, const char* string)
{
    unsigned count = 0;
    while(string[count] != '\0')
    {
        dest[count] = string[count];
        ++count;
    }

    return dest;
}


int main()
{
    char string1[1];
    assert(*my_strcpy(string1, "H") == 'H');

    char string3[10];
    my_strcpy(string3, "KKKKKKKKK\0");
    for(int i = 0; i < 9; ++i)
        assert(string3[i] == 'K');

    char string4[] = "ABCDEFG";
    char string5[] = "123456789";

    my_strcpy(string4 + 2, string5 + 7);

    char result[] = "AB89EFG";

    for(int i = 0; i < 7; ++i)
        assert(result[i] == string4[i]);

    char string6[1];
    my_strcpy(string6, "");
    assert(string6[0] != 0);

    return 0;
}
