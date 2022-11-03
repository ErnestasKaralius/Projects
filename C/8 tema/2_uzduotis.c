#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 256

long getFileSize(FILE* file)
{
    fseek(file, 0, SEEK_END);
    long size = ftell(file);

    return size;
}

char* find_largest_file(int argc, char** argv)
{
    long largest_size = 0;
    char* largest_name;

    for(int i = 1; i < argc; ++i)
    {
        FILE* file = fopen(*(argv + i), "rb");
        if(file != NULL)
        {
            long size = getFileSize(file);

            if(size >= largest_size)
            {
                largest_name = *(argv + i);
                largest_size = size;
            }

            fclose(file);
        }
    }

    return largest_name;
}

int main(int argc, char** argv)
{
    if(argc == 1)
        return 0;

    printf("%s\n", find_largest_file(argc, argv));

    return 0;
}
