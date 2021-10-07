#include "prog.h"
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

        mvprintw(10, 10, "owo");

        refresh();
    }
}

