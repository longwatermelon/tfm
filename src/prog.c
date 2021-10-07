#include "prog.h"
#include "fs.h"
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>


struct Prog* prog_alloc(const char* cwd)
{
    struct Prog* self = malloc(sizeof(struct Prog));
    self->running = true;

    prog_change_dir(self, cwd);

    return self;
}


void prog_free(struct Prog* self)
{
    for (int i = 0; i < self->nitems; ++i)
        free(self->items[i]);

    free(self->items);

    free(self);
}


void prog_mainloop(struct Prog* self)
{
    while (self->running)
    {
        int key = getch();
        erase();

        if (key == 'q')
            self->running = false;

        mvprintw(20, 2, "%s", self->cwd);
        prog_render_cwd(self);

        refresh();
    }
}


void prog_change_dir(struct Prog* self, const char* path)
{
    char* full_path = realpath(path, 0);
    memcpy(self->cwd, full_path, strlen(full_path));
    self->cwd[strlen(full_path)] = '\0';

    free(full_path);

    self->items = fs_list_directory(self->cwd, &self->nitems);
}


void prog_render_cwd(struct Prog* self)
{
    for (int i = 0; i < self->nitems; ++i)
    {
        mvprintw(1 + i, 2, "%s", self->items[i]);
    }
}

