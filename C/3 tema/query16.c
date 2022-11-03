#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
	char name[30];
	char surname[30];
	int course;					// year of study
	double average; 			// average grade

	int load; 					// number of courses
	char courses[10][30]; 		// course names
	int grades[10]; 			// course grades

	char languages[100];		// spoken languages

} Student;


int has_dublicate_strings(char string_array[][30], int length)
{
    for(int i=0; i < length - 1; i++)
        for(int j=i+1; j < length; j++)
            if(strcmp(string_array[i], string_array[j]) == 0)
                return 1;

    return 0;
}


int main(int argc, char *argv[]) {
	FILE *db = NULL;
	// open database file for reading, provide a parameter or use default "db.bin"
	if (argc > 1)
		db = fopen(argv[1], "rb");
	else
		db = fopen("db.bin", "rb");

	if (db){
		Student students[1000];			// all the data goes here
		int size = 0;					// how many students in database

		// reading data from file
		fread(&size, sizeof(int), 1, db);

		for (int i = 0; i < size; i++){
			fread(&students[i], sizeof(Student), 1, db);
		}
		printf("%d records loaded succesfully\n", size);

		// MODIFY CODE BELOW
		int counterDemo = 0; // for counting students

		for (int i = 0; i < size; ++i){ // process all the student records in database
			Student s = students[i]; // store data for each student in s

            int language_length = 0;
            char languages[10][30];

            // Get array of languages
            char* language = strtok(s.languages, " ");
            while(language != NULL)
            {
                strcpy(languages[language_length], language);
                language_length++;
                language = strtok(NULL, " ");
            }

            if(has_dublicate_strings(s.courses, s.load) || has_dublicate_strings(languages, language_length))
            {
                printf("%s %s\n", s.name, s.surname);
                ++counterDemo;
            }
		}
		printf("Filter applied, %d students found\n", counterDemo); // how many passed the filters
		fclose(db);
	} else {
		printf("File db.bin not found, check current folder\n");
	}

	return 0;
}
