
#ifndef _DIR_H_
#define _DIR_H_

int dir_exists(const char* path);
int dir_create(const char* path);
int dir_createsub(const char* path, const char* name);
int dir_rename(const char* path, const char* new_name);
int dir_delete(const char* path);
char* dir_absolute_path();

#endif
