#include <stdio.h>
#include <unistd.h>

long getFileSize(FILE* file)
{
    fseek(file, 0, SEEK_END);
    long size = ftell(file);

    return size;
}

int getValue(FILE* file, long index)
{
    char number;
    if(index < 1 || index > getFileSize(file))
        return -1;

    fseek(file, index - 1, SEEK_SET);
    fread(&number, 1, 1, file);

    return number - '0';
}

int setValue(FILE* file, int value, long index)
{
    char number = value + '0';
    if(index < 1 || index > getFileSize(file) + 1)
        return -1;

    fseek(file, index - 1, SEEK_SET);
    fwrite(&number, 1, 1, file);

    return 0;
}

int addValue(FILE* file, int value, long index)
{
    if(index < 1 || index > getFileSize(file) + 1)
        return -1;

    for(int i = getFileSize(file) + 1; i > index; --i)
        setValue(file, getValue(file, i - 1), i);

    setValue(file, value, index);

    return 0;
}

int remValue(FILE* file, int index)
{
    if(index < 1 || index > getFileSize(file))
        return -1;

    for(int i = index; i < getFileSize(file); ++i)
        setValue(file, getValue(file, i + 1), i);

    fseek(file, -1 , SEEK_END);
    ftruncate(fileno(file), ftell(file));

    return 0;
}

int main()
{
    FILE* file = fopen("text.txt", "r+b");

    // printf("%d\n", getValue(file, 1));
    // printf("%d\n", setValue(file, 9, 5));
    // printf("%d\n", addValue(file, 9, 2));
    // printf("%d", remValue(file, 1));

    fclose(file);
    return 0;
}
