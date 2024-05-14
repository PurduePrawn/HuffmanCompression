#ifndef TREE_H
#define TREE_H
#define NUM_BITS_IN_BYTE 8

// One tree node:
typedef struct TreeNode
{
    char character;
    long int frequency;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Stores info about a tree:
typedef struct Tree
{
    TreeNode *root;
    int leafCount;
    int nodeCount;
} Tree;

// Function declarations:

TreeNode *createTreeNode(char character, long int frequency);
Tree deleteTree(Tree tree);
void displayTree(TreeNode *node, int generation);

char *generatePostOrder(Tree tree, int length);

#endif // TREE_H
