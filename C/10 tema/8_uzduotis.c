#include <stdio.h>
#include <assert.h>
#include <string.h>

long unsigned my_strlen(const char* string)
{
    const char* ptr = string;
    while(*string != '\0')
        ++string;

    return string - ptr;
}

char* my_strchr(const char* string, int c)
{
    while(*string != '\0')
    {
        if(*string == (char)c)
            return (char *)string;

        ++string;
    }

    return NULL;
}

long unsigned my_strspn(const char* str1, const char* str2)
{
    char* ptr = (char*)str1;
    while(*ptr != '\0')
    {
        if(my_strchr(str2, *ptr) == NULL)
            return ptr - str1;

        ++ptr;
    }

    return my_strlen(str1);
}

char* my_strpbrk(const char* str1, const char* str2)
{
    while(*str1 != '\0')
    {
        if(my_strchr(str2, *str1) != NULL)
            return (char *)str1;

        ++str1;
    }

    return NULL;
}

char* my_strtok(char* string, const char* delim)
{
    static char* start_pos;

    if(string == NULL)
        string = start_pos;

    string += my_strspn(string, delim);
    if(*string == '\0')
    {
        start_pos = string;
        return NULL;
    }

    char* ptr = string;
    string = my_strpbrk(ptr, delim);

    if(string != NULL)
    {
        *string = '\0';
        start_pos = string + 1;
    }
    else
        start_pos = strchr(ptr, '\0');

    return ptr;
}

int main()
{
    char string1[20] = "h";
    char* ptr1 = my_strtok(string1, " ");
    assert(string1[0] == 'h' && string1[1] == '\0');

    char* ptr2 = my_strtok(NULL, " ");
    assert(ptr2 == NULL);

    char string[2] = "x\0";
    char* s = my_strtok(string, " ");
    assert(s[0] == 'x' && s[1] == '\0');

    char string2[30] = "Hello, World, Bye World\0";

    char* su = my_strtok(string2, "ko");
    assert(su[0] == 'H' && su[1] == 'e' && su[2] == 'l' && su[3] == 'l');

    char* sx = my_strtok(NULL, " ");
    assert(sx[0] == ',' && sx[1] == '\0');


    char string3[20] = " ";
    char* sy = my_strtok(string3, " ");
    assert(sy != NULL);

    return 0;
}
