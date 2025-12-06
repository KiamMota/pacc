#ifndef _PROJECT_H_
#define _PROJECT_H_

int proj_init(int argc, char** argv);

void proj_step_gitignore_gen(const char* projname);
void proj_step_createsrc(const char* projname);
void proj_step_createinclude(const char* projname);
void proj_step_writecmake(const char* projname);

#endif
