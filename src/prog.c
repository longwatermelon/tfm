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
    utils_free_array(self->items, self->nitems);

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
    struct stat sb;
    stat(path, &sb);

    if (!S_ISDIR(sb.st_mode))
        return;

    chdir(path);
    getcwd(self->cwd, sizeof(char) * PATH_MAX);

    utils_free_array(self->items, self->nitems);

    self->items = fs_list_directory(self->cwd, &self->nitems, DT_DIR, FS_INCLUDE);
    utils_sort_alphabetically(self->items, self->nitems);

    int nfiles;
    char** files = fs_list_directory(self->cwd, &nfiles, DT_DIR, FS_EXCLUDE);
    utils_sort_alphabetically(files, nfiles);

    self->items = realloc(self->items, sizeof(char*) * (self->nitems + nfiles));
    memcpy(&self->items[self->nitems], files, sizeof(char*) * nfiles);
    self->nitems += nfiles;

    free(files);

    self->selected = 0;
}


void prog_render_cwd(struct Prog* self)
{
    for (int i = 0; i < self->nitems; ++i)
    {
        if (self->selected == i)
            mvaddch(3 + i, 0, '>');

        struct stat sb;
        stat(self->items[i], &sb);

        char* name = fs_name(self->items[i]);

        {
            char* cwd_parent = fs_parent(self->cwd);

            if (cwd_parent)
            {
                if (strcmp(cwd_parent, self->items[i]) == 0)
                {
                    free(name);
                    name = malloc(sizeof(char) * 3);
                    sprintf(name, "..");
                }

                free(cwd_parent);
            }
        }

        if (name)
        {
            if (S_ISDIR(sb.st_mode))
                mvprintw(3 + i, 2, "[Directory]  %s", name);
            else
                mvprintw(3 + i, 2, "[File]       %s", name);

            free(name);
        }
        else
        {
            mvprintw(3 + i, 2, "<Error>");
        }
    }
}

