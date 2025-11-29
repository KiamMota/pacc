#include "cli/dispatch.h"
#include <stdio.h>
#include <strings.h>


static void help_msg()
{
  printf("pacc -- \t\n");
  printf("\t[init] (--lib/-l) -> inicia um projeto.\n");
  printf("\t[install] -> instala uma dependência.\n");
}

int main(int argc, char** argv) {
  if(argc <= 1)
  {
    help_msg();
    return 0;
  }

  cli_dispatch(argc, argv);

  return 0;
}

