#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#define NUM_BITS_IN_BYTE 8

// One tree node:
typedef struct TreeNode
{
    char character;
    char frequency;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// One node of a doubly linked list:
typedef struct ListNode
{
    TreeNode *tree;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode;

// A wrapper for a tree's root for clear communication:
typedef struct Tree
{
    TreeNode *root;
} Tree;

// A wrapper for a linked list's head and tail nodes:
typedef struct List
{
    ListNode *head;
    ListNode *tail;
} List;

typedef struct codeTableEntry
{
    char val;
    char *code;
} codeTableEntry;

// Function declarations:
TreeNode *generateHuffmanTree(int *charFrequencies, int length, int *numNodes);
TreeNode *generateTree(char *postOrder, int postOrderLength, int *numLeafs);
void displayTree(TreeNode *node, int generation);
void generateCodeTable(TreeNode *node, codeTableEntry *codeTable);
void compress(char *postOrder, int postOrderLength, codeTableEntry *codeTable, int codeTableLength, char *article, char *filename);

int listLength(List *list);
void appendListNode(List *list, TreeNode *tree);
void insertListNode(List *list, TreeNode *newTree, ListNode *left, ListNode *right);
void deleteListNode(List *list, ListNode *todelete);

TreeNode *createTreeNode(char character, int frequency);
TreeNode *deleteTree(TreeNode *root);

void addPostOrderEntry(TreeNode *tn, char *postOrder, int *index);
char *generatePostOrder(Tree tree, int length);

#endif
