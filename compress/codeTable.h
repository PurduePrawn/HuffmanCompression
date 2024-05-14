#ifndef CODE_TABLE
#define CODE_TABLE
#include "tree.h"
// One element of a code table (array) containing a character and its huffman code (as a string)
typedef struct codeTableEntry
{
    char val;
    char *code;
} codeTableEntry;

void generateCodeTable(TreeNode *node, codeTableEntry *codeTable);
char *getCode(codeTableEntry *codeTable, int tableLength, char val);
#endif // CODE_TABLE