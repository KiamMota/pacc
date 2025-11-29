#include <stdio.h>
#ifdef _WIN32
#include <io.h>
#define rm _unlink
#else
#include <unistd.h>
#define rm unlink
#endif

int file_exists(const char *n) {
    FILE *f = fopen(n, "r");
    if (!f) return 0;
    fclose(f);
    return 1;
}

int file_create(const char *n) {
    FILE *f = fopen(n, "wx");
    if (!f) return 1;
    fclose(f);
    return 0;
}

int file_overwrite(const char *n) {
    if (rm(n) != 0) return 1;
    FILE *f = fopen(n, "w");
    if (!f) return 1;
    fclose(f);
    return 0;
}

