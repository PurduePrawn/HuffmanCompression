#ifndef TREE_C
#define TREE_C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"

void displayTree(TreeNode *root, int generation)
{
    if (!root)
    {
        return;
    }

    for (int i = 0; i < generation; i++)
    {
        printf("  ");
    }
    printf("%c %d \n", root->character, root->frequency);

    displayTree(root->left, generation + 1);
    displayTree(root->right, generation + 1);
}

TreeNode *generateHuffmanTree(int *charFrequencies, int length, int *numNodes)
{
    List list = {.tail = NULL,
                 .head = NULL};
    // Copy sorted character frequency array into linked list:
    for (int i = 0; i < length; i += 2)
    {
        char character = charFrequencies[i];

        int frequency = charFrequencies[i + 1];

        // Create a tree node somewhere in the heap that stores the character and its count:
        TreeNode *tn = createTreeNode(character, frequency);
        *numNodes = *numNodes + 1;
        appendListNode(&list, tn);
        // printf("char: %c, ", tn->character);
        // printf("freq: %d \n", tn->frequency);
    }

    // While list has more than one entry:
    while (list.head != list.tail)
    {
        ListNode *first = list.head;
        ListNode *second = first->next;
        // printf("char1: %c, ", first->tree->character);
        // printf("freq1: %d \n", first->tree->frequency);
        // printf("char2: %c, ", second->tree->character);
        // printf("freq2: %d \n", second->tree->frequency);
        // Generate tree node with children as first two elements in linked list and frequency as sum of children's frequencies:
        TreeNode *subtree = createTreeNode(0, first->tree->frequency + second->tree->frequency);
        *numNodes = *numNodes + 1;
        subtree->left = first->tree;
        subtree->right = second->tree;
        // Delete first two nodes:
        deleteListNode(&list, first);
        deleteListNode(&list, second);

        // Find where to put subtree to maintain sorted frequencies and put it there:
        ListNode *ln = list.head;
        // printf("subtree: %d\n", subtree->frequency);
        while (ln != NULL && subtree->frequency >= ln->tree->frequency)
        {
            // printf("%c %d\n", ln->tree->character, ln->tree->frequency);
            ln = ln->next;
        }
        if (ln == NULL)
        {

            appendListNode(&list, subtree);
        }
        else
        {
            insertListNode(&list, subtree, ln->prev, ln);
        }
    }
    // Delete the one remaining list node holding the Huffman tree:
    TreeNode *root = list.head->tree;
    deleteListNode(&list, list.head);

    return root;
}

#endif
