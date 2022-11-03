#include <stdio.h>

long getFileSize(char* fileName)
{
    FILE* file = fopen(fileName, "rb");
    if(file == NULL)
        return -1;

    fseek(file, 0, SEEK_END);

    long size = ftell(file);
    fclose(file);

    return size;
}

int main()
{
    printf("%ld", getFileSize("text.txt"));

    return 0;
}
