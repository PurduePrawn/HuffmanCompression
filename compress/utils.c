#include "utils.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
// Allocate memory for a string and add all characters in the file into the string plus a null character:
void readFile(char *filename, char **arr, long int *length)
{
    FILE *fp = fopen(filename, "r");

    // Find size of file:
    fseek(fp, 0, SEEK_END);
    long int size = ftell(fp);
    *length = size / sizeof(char);

    // Allocate memory plus space for null character:
    *arr = malloc(size + sizeof(char));

    // Copy contents of file into array:
    fseek(fp, 0, SEEK_SET);
    fread(*arr, sizeof(char), size / sizeof(char), fp);

    // Add null character to end of allocated memory
    *(*arr + size) = '\0';

    fclose(fp);
}

bool countChar(char *filename, long int *counts, int size)
{
    // open a file whose name is filename for reading
    FILE *fp = fopen(filename, "r");
    // if fopen fails, return false. Do NOT fclose
    if (fp == NULL)
    {
        perror("countChar could not open file");
        return false;
    }

    int onechar; // Character ASCII value serving as an index for counts[]
    while ((onechar = fgetc(fp)) != EOF)
    {
        counts[onechar]++;
    }
    fclose(fp);
    return true;
}

// Compares given frequencies and returns positive if a is larger:
int cmpfunc(const void *a, const void *b)
{
    TreeNode *aCasted = (TreeNode *)a;
    TreeNode *bCasted = (TreeNode *)b;

    return ((*aCasted).frequency - (*bCasted).frequency);
}