#include <assert.h>

int my_strncmp(const char *str1, const char *str2, int n)
{
    for(int i = 0; i < n; ++i)
    {
        if(str1[i] > str2[i])
            return 1;

        if(str2[i] > str1[i])
            return -1;
    }

    return 0;
}

int main()
{

    assert(my_strncmp("h", "h", 1) == 0);
    assert(my_strncmp("", "", 0) == 0);
    assert(my_strncmp("ABC", "abc", 3) < 0);
    assert(my_strncmp("abc", "ABC", 3) > 0);
    assert(my_strncmp("Hello", "Hello", -1) == 0);
    assert(my_strncmp("\0555", "1\0\05", 100) < 0);
    assert(my_strncmp("a trtrtrtrtr", "a", 4) == 0);

    return 0;
}
