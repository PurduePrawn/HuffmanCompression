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