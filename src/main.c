#include "prog.h"
#include "utils.h"
#include "fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>


int main()
{
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    raw();
    curs_set(0);

    char* full_path = realpath(".", 0);
    struct Prog* p = prog_alloc(full_path);

    prog_mainloop(p);

    prog_free(p);
    free(full_path);

    curs_set(1);
    endwin();

    return 0;
}
