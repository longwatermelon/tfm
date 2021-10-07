#ifndef PROG_H
#define PROG_H

#include <stdbool.h>
#include <dirent.h>

struct Prog
{
    bool running;

    char cwd[PATH_MAX];
    
    char** items;
    int nitems;

    int selected;
};

struct Prog* prog_alloc(const char* cwd);
void prog_free(struct Prog* self);

void prog_mainloop(struct Prog* self);
void prog_handle_events(struct Prog* self, int key);

void prog_change_dir(struct Prog* self, const char* path);
void prog_render_cwd(struct Prog* self);

void prog_free_items(struct Prog* self);

#endif

