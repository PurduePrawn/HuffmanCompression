#ifndef COMPRESS
#define COMPRESS
#include "tree.h"
#include "codeTable.h"
void compress(char *postOrder, long int postOrderLength, codeTableEntry *codeTable, int codeTableLength, char *article, char *filename);
#endif // COMPRESS