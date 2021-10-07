#include "utils.h"
#include <stdio.h>
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

