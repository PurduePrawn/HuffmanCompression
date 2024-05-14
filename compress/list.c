#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

int listLength(List *list)
{
    int length = 1;
    ListNode *ln = list->head;
    while (ln != list->tail)
    {
        ln = ln->next;
        length++;
    }
    return length;
}

// Create and add a node (referencing a tree) to the end of a linked list:
void appendListNode(List *list, TreeNode *tree)
{

    // Loop control node
    ListNode *ln = list->head;

    // The list's current tail before appending new node
    ListNode *prevTail = NULL;

    // Go till end of list and also save its current tail:
    while (ln)
    {
        prevTail = ln;
        ln = ln->next;
    }

    // Allocate new list node and connect it to tail:
    ln = malloc(sizeof(ListNode));
    ln->next = NULL;
    ln->tree = tree;

    if (prevTail)
    {
        prevTail->next = ln;
        ln->prev = prevTail;
    }

    if (list->head == NULL)
    { // If empty list
        list->head = ln;
    }

    // ln is always the new tail, regardless of whether its the first element in the list:
    list->tail = ln;
}

void insertListNode(List *list, TreeNode *newTree, ListNode *left, ListNode *right)
{
    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->tree = newTree;
    newNode->prev = left;
    newNode->next = right;
    if (left == NULL)
    {
        list->head = newNode;
        printf("INSERTING AT HEAD\n");
    }
    else
    {
        left->next = newNode;
    }
    right->prev = newNode;
}

// Delete a node from a list:
void deleteListNode(List *list, ListNode *todelete)
{

    // Loop control node:
    ListNode *ln = list->head;

    // Go through list and find node to delete:
    while (ln != NULL)
    {
        if (ln == todelete)
        {

            // Connect surrounding nodes and set head and tail accordingly, then delete the node:
            if (ln->prev)
                ln->prev->next = ln->next;
            if (ln->next)
            {
                ln->next->prev = ln->prev;
            }
            if (ln == list->tail)
                list->tail = ln->prev;
            if (ln == list->head)
                list->head = ln->next;
            free(ln);
            return;
        }

        ln = ln->next;
    }
}
