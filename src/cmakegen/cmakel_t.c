#include "cmakegen/cmakel_t.h"
#include "utils/message.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

cmake_t* cmakel_init(const char* proj_path) {
    cmake_t* cmake = malloc(sizeof(cmake_t));
    if (!cmake) {
        msg_err("cannot alloc cmake_t");
        exit(1);
    }

    cmake->buffer = malloc(1);
    if (!cmake->buffer) {
        free(cmake);
        msg_err("cannot alloc buffer");
        exit(1);
    }
    cmake->buffer[0] = '\0';
    cmake->len = 0;

    char abs_path[5012];
    if (!realpath(proj_path, abs_path)) {
        free(cmake->buffer);
        free(cmake);
        msg_err("invalid project path");
        return NULL;
    }

    cmake->proj_path = strdup(abs_path); // garante path absoluto e terminado com \0
    if (!cmake->proj_path) {
        free(cmake->buffer);
        free(cmake);
        msg_err("cannot strdup path");
        return NULL;
    }

    return cmake;
}

void cmake_destroy(cmake_t **c)
{
  if(!c || !*c) return;
  (*c)->len = 0;
  free((*c)->buffer);
  free((*c)->proj_path);
  free(*c);
  *c = NULL;
}

void cmake_comment(cmake_t *c, const char *comment) {
    if (!comment) return;

    while (*comment == ' ') comment++;  // remove só espaços, não tabs

    size_t clen = strlen(comment);
    int needs_nl = clen == 0 || comment[clen - 1] != '\n';

    const char *prefix = "# ";
    size_t plen = 2;

    size_t extra = plen + clen + (needs_nl ? 1 : 0);
    size_t new_size = c->len + extra + 1;

    c->buffer = realloc(c->buffer, new_size);

    memcpy(c->buffer + c->len, prefix, plen);
    memcpy(c->buffer + c->len + plen, comment, clen);
    if (needs_nl)
        c->buffer[c->len + plen + clen] = '\n';

    c->len += extra;
    c->buffer[c->len] = '\0';
}

void cmake_minimum_required(cmake_t *cmake, const char *version)
{
  const char *fmt = "cmake_minimum_required(VERSION %s)\n";
  size_t line_len = snprintf(NULL, 0, fmt, version);
  char* line = malloc(line_len + 1);
  snprintf(line, line_len, fmt, version);

  size_t old = cmake->len;
  cmake->len = old + line_len;
  cmake->buffer = realloc(cmake->buffer, cmake->len + 1);
  memcpy(cmake->buffer + old, line, line_len + 1);
  free(line);
}

void cmake_project(cmake_t *c, const char *name, LANG_PROJ lang)
{
    if (!c || !name) return;

    const char *lang_str;
    switch (lang) {
        case LANG_C:   lang_str = "C"; break;
        case LANG_CPP: lang_str = "CXX"; break;
        case LANG_CPPC:
        default:       lang_str = "C CXX"; break;
    }

    size_t line_len = snprintf(NULL, 0, "project(%s %s)\n", name, lang_str);
    if (line_len == 0) return;

    // Aloca espaço temporário para a linha
    char *line = malloc(line_len + 1);
    if (!line) return;
    snprintf(line, line_len + 1, "project(%s %s)\n", name, lang_str);


    char *tmp = realloc(c->buffer, c->len + line_len + 1);
    if (!tmp) { free(line); return; }
    c->buffer = tmp;

    memcpy(c->buffer + c->len, line, line_len);
    c->len += line_len;
    c->buffer[c->len] = '\0';

    free(line);
}


void cmake_write(cmake_t *cmake)
{
  char* src_dir = malloc(strlen(cmake->proj_path) + strlen("/CMakeLists.txt") + 1); 
  strcpy(src_dir, cmake->proj_path);
  strcat(src_dir, "/cmakeists.txt");
  FILE* f = fopen(src_dir, "w");
  if(!f)
  {
    msg_err("no cmakeists.txt found.");
    exit(0);
  }
  
  fputs(cmake->buffer, f);
  fclose(f);
  free(src_dir);
}

void cmake_raw_write(const char *wath)
{
  


}
