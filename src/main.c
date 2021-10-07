#include "prog.h"
#include <stdio.h>
#include <ncurses.h>


int main()
{
    initscr();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    struct Prog* p = prog_alloc(".");
    prog_mainloop(p);
    prog_free(p);

    curs_set(1);
    endwin();

    return 0;
}
