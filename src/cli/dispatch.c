#include "cli/dispatch.h"
#include "services/proj.h"
#include "utils/message.h"
#include <string.h>

cli_function_list cli_list[] = {
    { "init", proj_init },
    { NULL, NULL }
};

void cli_dispatch(int argn, char **argv)
{
  for(int i= 0; cli_list[i].arg != NULL; i++)
  {
    if(strcmp(argv[1], cli_list[i].arg) == 0)
    {
      cli_list[i].function(argn, argv);
      return;
    }
  }
  msg_err("no command named '%s' found.");
}



