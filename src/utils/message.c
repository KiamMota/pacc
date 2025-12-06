#include "utils/message.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define CL_YEL() fputs("\x1b[33m", stdout);
#define CL_RED() fputs("\x1b[31m", stdout);
#define CL_NOR() fputs("\x1b[0m", stdout);

#define MSG_PACC_STDOUT() fputs("pacc: ", stdout);

#define MSG_PACC_STDOUT_ERR() \
  CL_RED();\
  fputs("pacc err: ", stdout);\
  CL_NOR();

#define MSG_PACC_STDOUT_WAR() \
  CL_YEL();\
  fputs("pacc warning: ", stdout);\
  CL_NOR();

#define MSG_PACC_STDOUT_FATAL() \
  CL_RED();\
  fputs("pacc fatal: ", stdout);\
  CL_NOR();

#define MSG_PACC_STDOUT_DEBUG() fputs("[PACC DEBUG]: ", stdout);

/*
 * Prints a message formatted as a log to stdout.
 *
 * @param str format string 
 * @param ... other args
 *
 * */

void msg(const char *str, ...)
{
  va_list args;
  va_start(args, str);
  MSG_PACC_STDOUT();
  vprintf(str, args);
  fputs("\n", stdout);
  va_end(args);
}

void msg_err(const char *str, ...)
{
  va_list args;
  va_start(args, str);
  MSG_PACC_STDOUT_ERR();
  vprintf(str, args);
  fputs("\n", stdout);
  va_end(args);
}

void msg_war(const char *str, ...)
{
  va_list args;
  va_start(args, str);
  MSG_PACC_STDOUT_WAR();
  vprintf(str, args);
  fputs("\n", stdout);
  va_end(args);
}

void msg_fatal(const char *str, int exit_status, ...)
{
  va_list args;
  va_start(args, str);
  MSG_PACC_STDOUT_FATAL();
  vprintf(str, args);
  fputs("\n", stdout);
  exit(exit_status);
}

void msg_debug(const char *str, ...)
{
  va_list args;
  va_start(args, str);
  fputs("[PACC DEBUG]:", stdout);
  vprintf(str, args);
  fputs("\n", stdout);
}

void msg_few_args(int required, int received)
{
  MSG_PACC_STDOUT_ERR();
  printf("to few args, expected %d, received %d.\n", required, received);
  printf("use -h or --help to see commands.\n");
  return;
}

int msg_choose(const char *question)
{
  printf("%s", question);
  printf(" [Y/n] ");
  char r = getc(stdin);
  switch (r) {
    case '\n': return 1;
    case 'Y': return 1;
    case 'y': return 1;
    default: return 0;
  } 
}
