#ifndef HEADER_LIST_INCLUDED
#define HEADER_LIST_INCLUDED
#include "tree.h"
// One node of a doubly linked list:
typedef struct ListNode
{
    TreeNode *tree;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode;

// A wrapper for a linked list's head and tail nodes:
typedef struct List
{
    ListNode *head;
    ListNode *tail;
} List;

// Create and add a node (referencing a tree) to the end of a linked list:
void appendListNode(List *list, TreeNode *tree);

// Insert list node containing newTree between left and right list nodes
void insertListNode(List *list, TreeNode *newTree, ListNode *left, ListNode *right);

// Delete a node from a list:
void deleteListNode(List *list, ListNode *todelete);

int listLength(List *list);

#endif // HEADER_LIST_INCLUDED