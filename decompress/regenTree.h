#ifndef TREE_H
#define TREE_H
#include "structures.h"
#include <stdio.h>
typedef unsigned char Byte;

// Using 0 indexing, gets bit from byte at given index and returns it as a 1 or 0
int getBit(Byte byte, int index);

TreeNode *regenTree(FILE *compressedFile, int *numLeafs, long int *postOrderEnd);
#endif