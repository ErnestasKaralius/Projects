#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 256

void open_checking_file(FILE** check_file)
{
    while(1)
    {
        char filename[MAX_NAME_LENGTH];

        printf("Iveskite tikrinamo failo varda: ");

        scanf("%[^\n]255s", filename);
        scanf("%*[^\n]");
        scanf("%*c");

        *check_file = fopen(filename, "r");

        if(*check_file == NULL)
            printf("Nepavyko atidaryti tekstinio failo!\n");
        else
            break;
    }
}

int is_a_number(char* word)
{
    for(int i = 0; i < strlen(word); ++i)
        if(!isdigit(word[i]))
            return 0;

    return 1;
}

void remove_new_line_symbol(char* line)
{
    char* end_line = strchr(line, '\n');
        if(end_line != NULL)
            strncpy(end_line, "\0", 1);
}

void convert_word(char* word)
{
    char end_symbols[7] = "!?.,;:\0";

    // Maybe add support for " ", ' '
    long unsigned length = strlen(word);
    if(strchr(end_symbols, word[length - 1]) != NULL)
        word[length - 1] = '\0';

    for(int i = 0; i < length; ++i)
        word[i] = tolower(word[i]);
}

int is_in_dictionary(FILE* dictionary, char* word)
{
    char dictionary_word[256];
    while(fscanf(dictionary, "%s", dictionary_word) != EOF)
        if(strcmp(word, dictionary_word) == 0)
            return 1;

    return 0;
}

int yes_or_no_prompt()
{
    while(1)
    {
        int answer = getchar();
        if(getchar() != '\n')
        {
            scanf("%*[^\n]");
            scanf("%*c");
        }
        else if(answer == 't')
            return 1;

        else if(answer == 'n')
            return 0;

        printf("Iveskite t/n: ");
    }
}

int main()
{
    FILE* check_file;
    FILE* mistake_file;
    FILE* dictionary;

    size_t size = MAX_NAME_LENGTH;

    printf("Si programa suranda klaidingai parasytus zodzius. Jei norite, galite zodzius itraukti i zodyna, kad jie nebuti laikomi klaidingais.\n");
    while(1)
    {
        mistake_file = fopen("mistakes.txt", "w");
        if(mistake_file == NULL)
        {
            printf("Nepavyko sukurti klaidu failo!\n");
            return 0;
        }

        char* line = malloc(size * sizeof(char));
        int line_count = 0, word_count = 0;

        if(line == NULL)
        {
            printf("Klaida alokuojant kaupa!\n");
            fclose(mistake_file);
            return 0;
        }

        open_checking_file(&check_file);

        printf("Ieskoma klaidu...\n");

        // Get every line until EOF
        while(getline(&line, &size, check_file) != -1)
        {
            ++line_count;
            remove_new_line_symbol(line);

            // Loop through every word in line
            char* word = strtok(line, " ");
            while(word != NULL)
            {
                dictionary = fopen("dictionary.txt", "a+");
                if(dictionary == NULL)
                {
                    printf("Nepavyko atidaryti zodyno!\n");
                    break;
                }

                ++word_count;
                if(!is_a_number(word))
                {
                    convert_word(word);

                    // If the word is not in the dictionary, ask to save it
                    if(is_in_dictionary(dictionary, word) == 0)
                    {
                        printf("Norite „%s“ itraukti i zodyna (t/n): ", word);
                        if(yes_or_no_prompt() == 1)
                            fprintf(dictionary, "%s\n", word);
                        else
                            fprintf(mistake_file, "%d eilutė, %d žodis (%s)\n", line_count, word_count, word);
                    }
                }
                fclose(dictionary);
                word = strtok(NULL, " ");
            }
        }

        printf("Daugiau klaidu nerasta!\n\n");

        fclose(check_file);
        fclose(mistake_file);
        free(line);

        printf("Norite patikrinti kita faila (t/n): ");
        if(yes_or_no_prompt() == 0)
            break;
    }

    return 0;
}
