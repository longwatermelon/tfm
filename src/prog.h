#ifndef PROG_H
#define PROG_H

#include <stdbool.h>
#include <dirent.h>

struct Prog
{
    bool running;

    char cwd[PATH_MAX];
};

struct Prog* prog_alloc(const char* cwd);
void prog_free(struct Prog* self);

void prog_mainloop(struct Prog* self);

#endif

