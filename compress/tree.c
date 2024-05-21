#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tree.h"
#include "list.h"
// Allocates and initialize tree node with value val:
TreeNode *createTreeNode(char character, long int frequency)
{
    TreeNode *tn = calloc(1, sizeof(TreeNode));
    tn->left = NULL;
    tn->right = NULL;
    tn->character = character;
    tn->frequency = frequency;
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
    if (root->character && root->character != '\n')
    {
        printf("%c \n", root->character);
    }
    else if (root->character == '\n')
    {
        printf("BREAK \n");
    }
    else
    {
        printf("- \n");
    }
    displayTree(root->left, generation + 1);
}

TreeNode *deleteTreeMemory(TreeNode *root)
{
    if (root == NULL)
        return NULL;

    root->left = deleteTreeMemory(root->left);
    root->right = deleteTreeMemory(root->right);
    free(root);

    return NULL;
}

Tree deleteTree(Tree tree)
{
    tree.root = deleteTreeMemory(tree.root);
    tree.nodeCount = 0;
    tree.leafCount = 0;
    return tree;
}

//----------------TREE POST ORDER EXPRESSION-----------------------------//

// Recursive post-order generator
void recursivePostOrderGen(TreeNode *tn, char *postOrder, int *index)
{
    if (tn == NULL)
        return;
    recursivePostOrderGen(tn->left, postOrder, index);
    recursivePostOrderGen(tn->right, postOrder, index);
    if (tn->character)
    {
        postOrder[*index] = 1; // Add control bit 1 if the character is not null (lead node)
        *index = *index + 1;
    }
    postOrder[*index] = tn->character; // Add the actual character (This would automatically add control bit 0s for middle tree node with null chars)
    *index = *index + 1;
}

// Main post-order generator
char *generatePostOrder(Tree tree, int length)
{
    if (tree.root == NULL)
    {
        return NULL;
    }
    int index = 0;
    char *postOrder = calloc(length, sizeof(char)); // Allocate just enough space to store control bits, characters, and terminating 0:
    recursivePostOrderGen(tree.root, postOrder, &index);
    postOrder[length - 1] = 0; // Terminating 0

    // UNCOMPRESSED POST ORDER:
    printf("UNCOMPRESSED POST ORDER: \n");
    for (int i = 0; i < index + 1; i++)
    {
        if (postOrder[i] <= 1)
        {
            printf("%d ", (int)postOrder[i]);
        }
        else
        {
            printf("%c ", postOrder[i]);
        }
    }
    printf("\n");

    return postOrder;
}
