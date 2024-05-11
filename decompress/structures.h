#ifndef HEADER_STRUCTURES_INCLUDED
#define HEADER_STRUCTURES_INCLUDED

// One tree node:
typedef struct TreeNode
{
    char val;
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

// A row of the code table
typedef struct codeTableEntry
{
    char val;
    char *code;
} codeTableEntry;

#endif // HEADER_STRUCTURES_INCLUDED