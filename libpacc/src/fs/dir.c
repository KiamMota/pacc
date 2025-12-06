
#include "utils/dir.h"
#include "libmkdir.h"

int dir_create(const char *path)
{
  return dirmk(path);
}

int dir_exists(const char *path)
{
  return direxists(path);
}

int dir_delete(const char *path)
{
  return dirrm(path);
}

int dir_rename(const char *path, const char *new_name)
{
  return dirmv(path, new_name);
}

int dir_createsub(const char* proj_name, const char* dir_name)
{
    size_t len = strlen(proj_name) + 1 + strlen(dir_name) + 1; // proj_name + '/' + dir_name + '\0'
    char* src = malloc(len);
    if (!src) return 1;
    snprintf(src, len, "%s/%s", proj_name, dir_name);
    dir_create(src);
    free(src);
    return 0;
}

char* dir_absolute_path()
{
  return dirgetcur();
}

