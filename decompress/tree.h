#ifndef HEADER_TREE_INCLUDED
#define HEADER_TREE_INCLUDED
#include "structures.h"

// Allocates and initialize tree node with value val:
TreeNode *createTreeNode(char val);
void displayTree(TreeNode *root, int generation);
// Recursive function to generate huffman codes:
void generateCodeEntries(TreeNode *node, codeTableEntry *codeTable, int *index, int iterations, int codeAsDecimal);
// Function to generate huffman codes:
void generateCodeTable(TreeNode *node, codeTableEntry *codeTable);
#endif // HEADER_TREE_INCLUDED