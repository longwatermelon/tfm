#ifndef FS_H
#define FS_H

enum
{
    FS_EXCLUDE,
    FS_INCLUDE
};

// type_inclusion: either FS_INCLUDE or FS_EXCLUDE
char** fs_list_directory(const char* path, int* nitems, unsigned char type, int type_inclusion);

#endif

