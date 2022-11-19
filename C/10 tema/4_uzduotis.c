#include <stdio.h>
#include <assert.h>

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

int main()
{
    assert(*my_strchr(" ", ' ') == ' ');
    assert(my_strchr("", ' ') == NULL);

    assert(*my_strchr("Hello, World!", '!') == '!');
    assert(*my_strchr("HHHHHHHHHHHHHHHHHHHHHHhHHHHHHHHHHHHHHhhHHHHHHHH", 'h') == 'h');
    assert(my_strchr("000000011123456789", 't') == NULL);
    assert(my_strchr("\0\n", '\n') == NULL);

    assert(my_strchr("\066\n55", '\n') == NULL);

    return 0;
}
