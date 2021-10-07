#ifndef UTILS_H
#define UTILS_H

void utils_log(const char* path, const char* fmt, ...);

// Only for arrays of dynamic strings
void utils_free_array(char** arr, int len);
// Sorts <arr> alphabetically
void utils_sort_alphabetically(char** arr, int len);

#endif

