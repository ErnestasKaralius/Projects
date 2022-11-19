#include <stdio.h>
#include <assert.h>

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

long unsigned my_strcspn(const char* str1, const char* str2)
{
    char* ptr = (char*)str1;
    while(*ptr != '\0')
    {
        if(my_strchr(str2, *ptr) != NULL)
            return ptr - str1;

        ++ptr;
    }

    return my_strlen(str1);
}


int main()
{
    assert(my_strcspn(" ", "") == 1);
    assert(my_strcspn("", "") == 0);
    assert(my_strcspn("", " ") == 0);
    assert(my_strcspn("heLLO", "HEllo") == 5);
    assert(my_strcspn("Hello", "Hellooooohello") == 0);
    assert(my_strcspn("HELL\n", "hell\n") == 4);
    assert(my_strcspn("HE\0LL\n", "he\0ll\n") == 2);

    assert(my_strcspn("1234\05", "") == 4);



    return 0;
}
