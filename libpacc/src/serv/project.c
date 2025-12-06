
#include "services/proj.h"
#include "cmakegen/cmake_gen.h"
#include "utils/dir.h"
#include "utils/message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void proj_step_gitignore_gen(const char* proj_name)
{
    const char* content[] = {
        "/build/\n",
        "/CMakeFiles/\n",
        "/cmake_install.cmake\n",
        "/Makefile\n",
        "compile_commands.json\n",
        ".cache/\n",
        "/extern/*\n",  // manter o diretório, ignorar conteúdo
        "!.gitignore\n", // garantir que o próprio gitignore não seja ignorado
        NULL
    };

    size_t len = strlen(proj_name) + strlen("/.gitignore") + 1;
    char* gitignore_path = malloc(len);
    if (!gitignore_path) return;

    snprintf(gitignore_path, len, "%s/.gitignore", proj_name);

    FILE* f = fopen(gitignore_path, "w");
    if (!f)
    {
        msg_err("It was not possible to create the .gitignore file.");
        free(gitignore_path);
        return;
    }

    for (int i = 0; content[i]; i++)
        fputs(content[i], f);

    fclose(f);
    free(gitignore_path);
}

void proj_step_createinclude(const char *projname)
{
  int size = strlen(projname) + strlen("include") + 2;
  char* fmt = malloc(size);
  snprintf(fmt, size, "%s/%s", projname, "include");
  if (!dir_exists(fmt)) 
  { 
    dir_create(fmt);  
    free(fmt);
    return;
  } 
  if (msg_choose("The include/ already exists. Do you want to overwrite?")) 
  { 
    dir_delete(fmt); 
    dir_create(fmt); 
  }
  free(fmt);
}

void proj_step_createsrc(const char *projname)
{
  int size = strlen(projname) + strlen("src") + 2;
  char* fmt = malloc(size);
  snprintf(fmt, size, "%s/%s", projname, "src");
  if(!dir_exists(fmt))
  {
    dir_create(fmt);
    free(fmt);
    return;
  }
  if(msg_choose("The src/ already exists. Do you want to overwrite?"))
  {
    dir_delete(fmt);
    dir_create(fmt);
  }
  free(fmt);
}


int proj_init(int argn, char** argv)
{
  if(argn < 3)
  {
    msg_few_args(3, argn);
    return 1;
  }

  /*
   * tratação do argv
   * */

  if(dir_exists(argv[2]))
  {
    if(!msg_choose("The directory already exists. Do you want to overwrite it?"))
    goto done;
  }
  dir_create(argv[2]);
  /* creating src */

  proj_step_createinclude(argv[2]);
  proj_step_createsrc(argv[2]);
  cmake_create_file(argv[2]);
  if(msg_choose("Do you want to generate a .gitignore file?"))
    proj_step_gitignore_gen(argv[2]);
  if(!msg_choose("Do you want to pre-configure your CMakeLists.txt?")) goto done;

done:
  return 0;
}
