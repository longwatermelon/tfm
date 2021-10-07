#include "prog.h"
#include "fs.h"
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>


struct Prog* prog_alloc(const char* cwd)
{
    struct Prog* self = malloc(sizeof(struct Prog));
    self->running = true;

    memcpy(self->cwd, cwd, strlen(cwd));
    self->cwd[strlen(cwd)] = '\0';

    return self;
}


void prog_free(struct Prog* self)
{
    free(self);
}


void prog_mainloop(struct Prog* self)
{
    while (self->running)
    {
        int key = getch();
        erase();

        prog_render_cwd(self);

        refresh();
    }
}


void prog_render_cwd(struct Prog* self)
{
    int nitems;
    char** items = fs_list_directory(self->cwd, &nitems);

    for (int i = 0; i < nitems; ++i)
    {
        mvprintw(1 + i, 2, "%s", items[i]);
        free(items[i]);
    }

    free(items);
}

