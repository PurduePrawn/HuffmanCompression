#ifndef UTILS
#define UTILS
#include <stdbool.h>

// Allocate memory for a string and add all characters in the file into the string plus a null character:
void readFile(char *filename, char **arr, long int *length);

bool countChar(char *filename, long int *counts, int size);

int cmpfunc(const void *a, const void *b);
#endif // UTILS