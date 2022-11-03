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


int string_is_in_array(char string[], int length, char array[][30])
{
    for(int i=0; i < length; i++)
        if(strcmp(string, array[i]) == 0) return 1;

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


		int name_length = size;
		char names[1000][30];
		int surname_length = size;
		char surnames[1000][30];

        for(int i=0; i < size; i++)
        {
            strcpy(names[i], students[i].name);
            strcpy(surnames[i], students[i].surname);
        }

        for(int i=0; i < name_length - 1; i++)
        {
            int has_dublicates = 0;
            for(int j=i+1; j < name_length; j++)
                if(strcmp(names[i], names[j]) == 0)
                {
                    has_dublicates = 1;
                    strcpy(names[j], names[name_length - 1]);
                    j--;
                    name_length--;
                }

            if(has_dublicates)
            {
                strcpy(names[i], names[name_length - 1]);
                i--;
                name_length--;
            }
        }
        // Should be a function, but didn't work out
        for(int i=0; i < surname_length - 1; i++)
        {
            int has_dublicates = 0;
            for(int j=i+1; j < surname_length; j++)
                if(strcmp(surnames[i], surnames[j]) == 0)
                {
                    has_dublicates = 1;
                    strcpy(surnames[j], surnames[surname_length - 1]);
                    j--;
                    surname_length--;
                }

            if(has_dublicates)
            {
                strcpy(surnames[i], surnames[surname_length - 1]);
                i--;
                surname_length--;
            }
        }

		// MODIFY CODE BELOW
		int counterDemo = 0; // for counting students

		for (int i = 0; i < size; ++i){ // process all the student records in database
			Student s = students[i]; // store data for each student in s

			if(string_is_in_array(students[i].name, name_length, names) || string_is_in_array(students[i].surname, surname_length, surnames)){
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
