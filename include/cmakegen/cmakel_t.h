#ifndef _CMAKE_T_H_
#define _CMAKE_T_H_

#include <stddef.h>
typedef struct
{
  char* buffer;
  size_t len;
  char* proj_path;
}cmake_t;

typedef enum
{
  LANG_CPPC,
  LANG_C,
  LANG_CPP
}LANG_PROJ;

cmake_t* cmakel_init(const char* proj_path);
void cmakel_destroy(cmake_t** c);
void cmakel_minimum_required(cmake_t* cmakel, const char* version);
void cmakel_comment(cmake_t* cmakel, const char* comment);
void cmakel_project(cmake_t* cmakel, const char* name, LANG_PROJ);
void cmakel_set(cmake_t* cmakel, char* name, const char* list);
void cmakel_raw_write(const char* wath);
void cmakel_write(cmake_t* cmakel);

#endif
