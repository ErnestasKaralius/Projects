#include <assert.h>

void* my_memset(void* str, int c, int n)
{
    unsigned char* ptr = str;

    for(int i = 0; i < n; ++i)
        ptr[i] = (char)c;

    return str;
}

int main()
{
    char string1[6] = "Hello\0";
    my_memset(string1, '$', 5);

    for(int i = 0; i < 5; ++i)
        assert(string1[i] == '$');


    char symbol;
    my_memset(&symbol, ' ', 1);
    assert(symbol == ' ');


    char string2[5]= "####\0";
    my_memset(string2 + 5, '$', 5);

    for(int i = 0; i < 4; ++i)
        assert(string2[i] == '#');

    char string3[3] = "hh";
    my_memset(string3, '!', 2);

    assert(string3[0] != '!' || string3[1] != '!');

    return 0;
}
