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

int main()
{
    assert(*my_strpbrk("Hello", "Hello") == 'H');
    assert(my_strpbrk("", "") == NULL);
    assert(my_strpbrk("", " ") == NULL);
    assert(my_strpbrk("1234567", "89") == NULL);
    assert(*my_strpbrk("aaabbbb", "AAAAAAAb") == 'b');

    assert(my_strpbrk("j\0j", "\0j") != NULL);

    return 0;
}
