#include "prog.h"
#include <stdio.h>
#include <ncurses.h>


int main()
{
    initscr();
    noecho();

    struct Prog* p = prog_alloc(".");
    prog_mainloop(p);
    prog_free(p);

    endwin();

    return 0;
}
