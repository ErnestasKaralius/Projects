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
	int language_amount;

} Student;

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

        int most_languages = 0;
        for(int i=0; i<size; ++i)
        {
            char temp_languages[100];
            strcpy(temp_languages, students[i].languages);

            students[i].language_amount = 0;

            char* language = strtok(temp_languages, " ");
            while(language != NULL)
            {
                students[i].language_amount++;
                language = strtok(NULL, " ");
            }
            if(students[i].language_amount > most_languages)
                most_languages = students[i].language_amount;
        }

		for (int i = 0; i < size; ++i){ // process all the student records in database
			Student s = students[i]; // store data for each student in s

            if (s.language_amount == most_languages) // *** third filter, various other conditions
            {
                printf("%s %s\n", s.name, s.surname); // print student data
                ++counterDemo; // counting students
            }
		}
		printf("Filter applied, %d students found\n", counterDemo); // how many passed the filters
		fclose(db);
	} else {
		printf("File db.bin not found, check current folder\n");
	}

	return 0;
}
