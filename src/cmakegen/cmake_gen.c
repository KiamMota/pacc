#include "cmakegen/cmake_gen.h"
#include "utils/message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cmake_create_file(const char* proj_path)
{ 
    int sz = snprintf(NULL, 0, "%s/CMakeLists.txt", proj_path) + 1;
    char* cmake_path = malloc(sz);
    if (!cmake_path) return;

    snprintf(cmake_path, sz, "%s/CMakeLists.txt", proj_path);

    FILE* f = fopen(cmake_path, "w");
    if (!f)
        msg_err("cannot write CMakeLists.txt");
    else
        fclose(f);

    free(cmake_path);
}

