#include "prog.h"
#include "fs.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
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
    prog_free_items(self);

    free(self);
}


void prog_mainloop(struct Prog* self)
{
    while (self->running)
    {
        int key = getch();
        erase();

        prog_handle_events(self, key);

        mvprintw(0, 2, "Current dir: %s", self->cwd);
        mvprintw(1, 2, "Press 'q' to exit");
        prog_render_cwd(self);

        refresh();
        usleep(1000);
    }
}


void prog_handle_events(struct Prog* self, int key)
{
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

    if (key == 's')
        prog_change_dir(self, self->items[self->selected]);
}


void prog_change_dir(struct Prog* self, const char* path)
{
    // Check if directory
    struct stat sb;
    stat(path, &sb);

    if (!S_ISDIR(sb.st_mode))
        return;

    chdir(path);
    getcwd(self->cwd, sizeof(char) * PATH_MAX);

    prog_free_items(self);

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


void prog_free_items(struct Prog* self)
{
    for (int i = 0; i < self->nitems; ++i)
        free(self->items[i]);

    free(self->items);
}

