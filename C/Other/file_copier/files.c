#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

#define BUFFER_LENGTH 512
#define FILENAME_LENGTH 1056

#if __WIN32
    #define DIR_SEPERATOR "\\"
#else
    #define DIR_SEPERATOR "/"
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
    strcat(path, DIR_SEPERATOR);
    strcat(path, new_entry);

    return path;
}

int copy_file(const char* source_path, const char* destination_path)
{
    if(strcmp(source_path, destination_path) == 0)
    {
        printf("CAN'T COPY FILE \"%s\" TO ITSELF\n", source_path);
        return -1;
    }

    FILE* source_file = fopen(source_path, "rb");
    if(source_file == NULL)
    {
        printf("FAILED TO READ FILE \"%s\": %s\n", source_path, strerror(errno));
        return -1;
    }
    FILE* new_file = fopen(destination_path, "wb");
    if(new_file == NULL)
    {
        printf("FAILED TO CREATE FILE \"%s\": %s\n", destination_path, strerror(errno));
        fclose(source_file);
        return -1;
    }

    char buffer[BUFFER_LENGTH];
    while(!feof(source_file))
    {
        size_t read_amount = fread(buffer, sizeof(char), BUFFER_LENGTH, source_file);
        fwrite(buffer, sizeof(char), read_amount, new_file);
    }

    fclose(source_file);
    fclose(new_file);
    return 0;
}

void copy_directory(const char* path, const char* copy_path)
{
    DIR* directory = opendir(path);
    if(directory == NULL)
    {
        printf("COULDN'T OPEN DIRECTORY \"%s\": %s\n", path, strerror(errno));
        return;
    }

    // If a Directory exists, we don't need to create a new one
    if(mkdir_function == -1 && errno != EEXIST)
    {
        printf("COULDN'T CREATE DIRECTORY \"%s\": %s\n", copy_path, strerror(errno));
        return;
    }

    struct dirent* dr;
    while((dr = readdir(directory)) != NULL) // Iterate through contents of a Directory
    {
        if(dr->d_name[0] == '.')
            continue;

        char* file_path = create_path(path, dr->d_name);
        char* new_path = create_path(copy_path, dr->d_name);

        if(dr->d_type == DT_DIR) // If another Directory is found, iterate through it
            copy_directory(file_path, new_path);

        else // Copy files to destination Directory
            copy_file(file_path, new_path);

        free(file_path);
        free(new_path);
    }
    closedir(directory);
}
