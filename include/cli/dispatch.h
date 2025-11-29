#ifndef _DISPATCH_H_
#define _DISPATCH_H_

typedef struct
{
  char* arg;
  int (*function)(int, char** );
} cli_function_list;

extern cli_function_list cli_list[];

void cli_dispatch(int argn, char** command);

#endif
