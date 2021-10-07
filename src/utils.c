#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


void utils_log(const char* path, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    FILE* fp = fopen(path, "a+");
    vfprintf(fp, fmt, args);
    fclose(fp);

    va_end(args);
}


void utils_free_array(char** arr, int len)
{
    for (int i = 0; i < len; ++i)
        free(arr[i]);

    free(arr);
}

