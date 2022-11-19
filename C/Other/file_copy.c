#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

#define FILENAME_LENGTH 1056
#define ARGUMENT_COUNT 3

#ifdef __WIN32
    #define dir_seperator "\\"
#else
    #define dir_seperator "//"
#endif

#if __linux__
    #define mkdir_function mkdir(copy_path, S_IRWXU)
#else
    #define mkdir_function mkdir(copy_path)
#endif

char* create_path(const char* current_path, const char* new_entry)
{
    if(strlen(current_path) + strlen(new_entry) > FILENAME_LENGTH - 1)
    {
        printf("UNABLE TO CREATE PATHNAME, LENGTH EXCEEDS %d", FILENAME_LENGTH - 1);
        exit(EXIT_FAILURE);
    }

    char* path = malloc(FILENAME_LENGTH);
    if(path == NULL)
    {
        perror("MEMORY ALLOCATION FAILURE\n");
        exit(EXIT_FAILURE);
    }

    strcpy(path, current_path);
    strcat(path, dir_seperator);
    strcat(path, new_entry);

    return path;
}

int copy_file(const char* source_path, const char* destination_path)
{
    FILE* source_file = fopen(source_path, "rb");
    if(source_file == NULL)
    {
        printf("FAILED TO READ FILE \"%s\"\n", source_path);
        return -1;
    }
    FILE* new_file = fopen(destination_path, "wb");
    if(new_file == NULL)
    {
        printf("FAILED TO CREATE FILE \"%s\"\n", destination_path);
        fclose(source_file);
        return -1;
    }

    // Go to EOF and calculate length
    fseek(source_file, 0, SEEK_END);
    long size = ftell(source_file);
    fseek(source_file, 0, SEEK_SET);

    for(int i = 0; i < size; ++i)
        putc(getc(source_file), new_file);

    fclose(source_file);
    fclose(new_file);
    return 0;
}

void copy_directory(const char* path, const char* copy_path)
{
    DIR* directory = opendir(path);
    if(directory == NULL)
    {
        printf("COULDN'T OPEN DIRECTORY \"%s\"\n", path);
        return;
    }

    // If a Directory exists, we don't need to create a new one
    if(mkdir_function == -1 && errno != EEXIST)
    {
        if(errno == EACCES)
            printf("WRITE NOT ALLOWED IN PARENT DIRECTORY of\"%s\"\n", copy_path);
        else if(errno == ENAMETOOLONG)
            printf("PATHNAME \"%s\" IS TOO LONG!\n", copy_path);
        else
            printf("MKDIR FAILURE\n");

        return;
    }

    struct dirent* dr;
    while((dr = readdir(directory)) != NULL) // Iterate through contents of a Directory
    {
        if(dr->d_name[0] == '.')
            continue;

        char* file_path = create_path(path, dr->d_name);
        // If another Directory is found, iterate through it
        if(dr->d_type == DT_DIR)
        {
            char* new_copy_path = create_path(copy_path, dr->d_name);
            copy_directory(file_path, new_copy_path);
            free(new_copy_path);
        }
        // Copy files to destination
        else
        {
            char* destination_path = create_path(copy_path, dr->d_name);
            copy_file(file_path, destination_path);
            free(destination_path);
        }
        free(file_path);
    }
    closedir(directory);
}

int main(int argc, char* argv[])
{
    if(argc != ARGUMENT_COUNT)
    {
        printf("Specify source folder and the destination\n");
        exit(EXIT_FAILURE);
    }

    copy_directory(argv[1], argv[2]);

    exit(EXIT_SUCCESS);
}
