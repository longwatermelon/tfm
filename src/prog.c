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
    self->selected = 0;

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

        if (key == KEY_UP || key == 'k')
        {
            --self->selected;

            if (self->selected < 0)
                self->selected = 0;
        }

        if (key == KEY_DOWN || key == 'j')
        {
            ++self->selected;

            if (self->selected >= self->nitems)
                self->selected = self->nitems - 1;
        }

        mvprintw(0, 2, "Current dir: %s", self->cwd);
        mvprintw(1, 2, "Press 'q' to exit");
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
    self->selected = 0;
}


void prog_render_cwd(struct Prog* self)
{
    for (int i = 0; i < self->nitems; ++i)
    {
        if (self->selected == i)
            mvaddch(3 + i, 0, '>');

        mvprintw(3 + i, 2, "%s", self->items[i]);
    }
}

