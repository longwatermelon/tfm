#include "fs.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ncurses.h>


char** fs_list_directory(const char* path, int* nitems, unsigned char type, int type_inclusion)
{
    DIR* dir = opendir(path);

    if (!dir)
    {
        utils_log("log", "Couldn't open dir %s\n", path);
        return 0;
    }

    char** items = malloc(0);
    *nitems = 0;

    struct dirent* de;

    while ((de = readdir(dir)) != 0)
    {
        if (strcmp(de->d_name, ".") == 0 ||
            (de->d_type != type && type_inclusion == FS_INCLUDE) ||
            (de->d_type == type && type_inclusion == FS_EXCLUDE))
            continue;

        items = realloc(items, sizeof(char*) * ++*nitems);
        items[*nitems - 1] = malloc(sizeof(char) * (strlen(de->d_name) + 1));
        memcpy(items[*nitems - 1], de->d_name, strlen(de->d_name) + 1);
    }

    closedir(dir);

    return items;
}

