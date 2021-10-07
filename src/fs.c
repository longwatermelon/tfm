#include "fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ncurses.h>


char** fs_list_directory(const char* path, int* nitems)
{
    DIR* dir = opendir(path);

    if (!dir)
    {
        fprintf(stderr, "Couldn't open directory %s\n", path);
        return 0;
    }

    char** items = malloc(0);
    *nitems = 0;

    struct dirent* de;

    while ((de = readdir(dir)) != 0)
    {
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
            continue;

        items = realloc(items, sizeof(char*) * ++*nitems);
        items[*nitems - 1] = malloc(sizeof(char) * (strlen(de->d_name) + 1));
        memcpy(items[*nitems - 1], de->d_name, strlen(de->d_name) + 1);
    }

    closedir(dir);

    return items;
}

