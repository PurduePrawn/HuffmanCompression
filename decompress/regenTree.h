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

typedef unsigned char Byte;
TreeNode *
regenTree(FILE *compressedFile, int *numLeafs, long int *postOrderEnd);

#endif