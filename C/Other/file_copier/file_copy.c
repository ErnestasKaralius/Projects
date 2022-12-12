#include <stdio.h>
#include <string.h>
#include "files.h"

#define ARGUMENT_COUNT 3

int main(int argc, char** argv)
{
    if(argc != ARGUMENT_COUNT)
    {
        printf("Specify source folder and the destination\n");
        return 1;
    }

    if(strcmp(argv[1], argv[2]) == 0)
    {
        printf("Can't copy folder to itself\n");
        return 1;
    }

    copy_directory(argv[1], argv[2]);
    return 0;
}
