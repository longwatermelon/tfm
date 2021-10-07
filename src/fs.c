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

        char* full_path = realpath(de->d_name, 0);
        items[*nitems - 1] = full_path;
    }

    closedir(dir);

    return items;
}


char* fs_name(const char* path)
{
    for (int i = strlen(path) - 1; i >= 0; --i)
    {
        if (path[i] == '/')
        {
            char* name = malloc(sizeof(char) * (strlen(path) - i + 1));
            snprintf(name, strlen(path) - i + 1, "%s", &path[i + 1]);
            return name;
        }
    }

    return 0;
}


char* fs_parent(const char* path)
{
    for (int i = strlen(path) - 1; i >= 0; --i)
    {
        if (path[i] == '/')
        {
            char* parent = malloc(sizeof(char) * (i + 1));
            snprintf(parent, i + 1, "%s", path);
            return parent;
        }
    }

    return 0;
}

