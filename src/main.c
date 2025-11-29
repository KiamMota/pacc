#include "cli/dispatch.h"
#include "utils/message.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

#define PACC_VER "1.0a"

static void version_msg()
{
  msg("%s", PACC_VER);
}

static void help_msg()
{
  printf("pacc \t\n");
  printf("\t[init] (--lib/-l) -> inicia um projeto.\n");
  printf("\t[install] -> instala uma dependência.\n");
}

int main(int argc, char** argv) {
  if(argc <= 1)
  {
    help_msg();
    return 0;
  }

  if(!strcmp(argv[1], "--help"))
  {
    help_msg();
    return 0;
  }

  if(!strcmp(argv[1], "-h"))
  {
    help_msg();
    return 0;
  }


  cli_dispatch(argc, argv);

  return 0;
}

