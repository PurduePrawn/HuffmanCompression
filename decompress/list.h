#ifndef HEADER_LIST_INCLUDED
#define HEADER_LIST_INCLUDED

#include "structures.h"

// Create and add a node (referencing a tree) to the end of a linked list:
void appendListNode(List *list, TreeNode *tree);

// Insert list node containing newTree between left and right list nodes
void insertListNode(List *list, TreeNode *newTree, ListNode *left, ListNode *right);

// Delete a node from a list:
void deleteListNode(List *list, ListNode *todelete);

#endif // HEADER_LIST_INCLUDED