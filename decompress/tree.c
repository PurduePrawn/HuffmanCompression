#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

// Allocates and initialize tree node with value val:
TreeNode *createTreeNode(char val)
{
    TreeNode *tn = malloc(sizeof(TreeNode));
    tn->left = NULL;
    tn->right = NULL;
    tn->val = val;
    return tn;
}

// Displays a binary tree sideways:
void displayTree(TreeNode *root, int generation)
{
    if (!root)
    {
        return;
    }
    displayTree(root->right, generation + 1);

    for (int i = 0; i < generation; i++)
    {
        printf("        ");
    }
    if (root->val && root->val != '\n')
    {
        printf("%c \n", root->val);
    }
    else if (root->val == '\n')
    {
        printf("BREAK \n");
    }
    else
    {
        printf("- \n");
    }
    displayTree(root->left, generation + 1);
}

// Recursive function to generate huffman codes:
void generateCodeEntries(TreeNode *node, codeTableEntry *codeTable, int *index, int iterations, int codeAsDecimal)
{
    // BASE CASE:
    if (!node)
        return;

    // If the current node is a leaf node, add its code string to the code table:
    if (node->val)
    {
        codeTable[*index].val = node->val;
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