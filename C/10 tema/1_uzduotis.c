#include <assert.h>

long unsigned my_strlen(const char* string)
{
    const char* ptr = string;
    while(*string != '\0')
        ++string;

    return string - ptr;
}

int main()
{

    assert(my_strlen("") == 0);
    assert(my_strlen("\0") == 0);
    assert(my_strlen("He\0llo\0") == 2);
    assert(my_strlen("Yes") == -1);

    return 0;
}
