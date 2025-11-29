#ifndef _MESSAGE_H_
#define _MESSAGE_H_

void msg(const char* str, ...);
void msg_err(const char* str, ...);
void msg_war(const char* str, ...);
void msg_fatal(const char* str, int exit_status, ...);
void msg_debug(const char* str, ...);
void msg_few_args(int required, int received);
int msg_choose(const char* question);

#endif
