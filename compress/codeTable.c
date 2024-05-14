#include "codeTable.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
// Recursive helper function to generate huffman codes:
void generateCodeEntries(TreeNode *node, codeTableEntry *codeTable, int *index, int iterations, int codeAsDecimal)
{
    // BASE CASE:
    if (!node)
        return;

    // If the current node is a leaf node, add its code string to the code table:
    if (node->character)
    {
        codeTable[*index].val = node->character;
        codeTable[*index].code = malloc(iterations + 1);
        sprintf(codeTable[*index].code, "%0*d", iterations, codeAsDecimal);
        *index = *index + 1;
    }

    // Run the function again for the node's left and right subtrees.
    // Increment iterations and calculate new codeAsDecimal value's according to the direction:
    generateCodeEntries(node->left, codeTable, index, iterations + 1, codeAsDecimal * 10);
    generateCodeEntries(node->right, codeTable, index, iterations + 1, codeAsDecimal * 10 + 1);
}

// Function to generate huffman codes:
void generateCodeTable(TreeNode *node, codeTableEntry *codeTable)
{
    int tableIndex = 0;
    int iterations = 0;
    int codeAsDecimal = 0;
    generateCodeEntries(node, codeTable, &tableIndex, iterations, codeAsDecimal);
}

// Function to retrieve a code from the code table:
char *getCode(codeTableEntry *codeTable, int tableLength, char val)
{
    for (int i = 0; i < tableLength; i++)
    {
        if (codeTable[i].val == val)
            return codeTable[i].code;
    }
    return NULL;
}