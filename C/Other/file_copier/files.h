#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

void copy_directory(const char* path, const char* copy_path);

char* create_path(const char* current_path, const char* new_entry);
int copy_file(const char* source_path, const char* destination_path);


#endif // FILES_H_INCLUDED
