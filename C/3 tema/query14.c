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

int has_listed_course(char course[], char courses_with_multiple_students[][30], int amount)
{
    for(int i=0; i < amount; i++)
        if(strcmp(course, courses_with_multiple_students[i]) == 0)
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


		int amount = 10;
        char multiple_student_courses[10][30] = {
            "Algebra", "Computer programming", "Operating systems", "Physics", "Philosophy",
            "Calculus", "Set theory", "Algorithms", "Discrete mathematics", "Computer networks"
        };

        for(int i=0; i < amount; i++)
        {
            // Loop through students
            int repeat_count = 0;
            for(int j=0; j < size; j++)
            {
                // Loop through courses
                for(int k=0; k < students[j].load; k++)
                    if(strcmp(students[j].courses[k], multiple_student_courses[i]) == 0)
                    {
                        repeat_count++;
                        break;
                    }

                if(repeat_count > 1) break;
            }

            // If course has 1 or less students, we remove it from the list
            if(repeat_count <= 1)
            {
                strcpy(multiple_student_courses[i], multiple_student_courses[amount - 1]);
                amount--;
                i--;
            }
        }

		// MODIFY CODE BELOW
		int counterDemo = 0; // for counting students

		for (int i = 0; i < size ; ++i)
        {
			Student s = students[i]; // store data for each student in s

			int is_the_only_student = 0;
			for(int j=0; j < s.load; j++)
                if(!has_listed_course(s.courses[j], multiple_student_courses, amount))
                {
                    is_the_only_student = 1;
                    break;
                }

            if(!is_the_only_student)
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
