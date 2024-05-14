#include "genTree.h"
#include "list.h"
#include <stdio.h>
// Creates a huffman tree in memory and returns handle for that tree:
Tree generateHuffmanTree(TreeNode *leafs, int numLeafs)
{
    List list = {0};
    Tree huffmanTree = {
        .root = NULL,
        .leafCount = numLeafs,
        .nodeCount = numLeafs // Total node count must include leaf count:
    };

    printf("\n");
    // Copy sorted leaf node array into linked list:
    for (int i = 0; i < numLeafs; i++)
    {

        appendListNode(&list, &leafs[i]);
        printf("Leaf: %c, %ld\n", list.tail->tree->character, list.tail->tree->frequency);
    }
    int count = 0;
    // While list has more than one entry:
    while (list.head != list.tail)
    {
        count++;
        ListNode *l = list.head;
        printf("ROUND %d\n\n", count);
        int listSize = 0;
        while (l)
        {
            listSize++;

            printf("TREE: \n");
            displayTree(l->tree, 0);
            printf("freq: %ld\n", l->tree->frequency);
            printf("\n");

            l = l->next;
        }
        printf("SIZE: %d\n", listSize);
        printf("HEAD: %c, %ld\nTAIL: %c, %ld\n", list.head->tree->character, list.head->tree->frequency, list.tail->tree->character, list.tail->tree->frequency);
        ListNode *first = list.head;        // Least common char
        ListNode *second = list.head->next; // Second least common char

        // Generate charLess tree node with children as first two elements in linked list and frequency as sum of children's frequencies:
        TreeNode *subtree = createTreeNode('\0', first->tree->frequency + second->tree->frequency);
        huffmanTree.nodeCount++; // New node created
        subtree->left = first->tree;
        subtree->right = second->tree;

        // Delete first two nodes:
        deleteListNode(&list, first);
        deleteListNode(&list, second);

        // Find where to put subtree to maintain sorted frequencies and put it there:
        ListNode *ln = list.head;
        while (ln != NULL && subtree->frequency >= ln->tree->frequency)
        {
            ln = ln->next;
        }
        if (ln == NULL) // If reached end of list
        {

            appendListNode(&list, subtree);
        }
        else
        {
            insertListNode(&list, subtree, ln->prev, ln);
        }
    }
    printf("generateHuffmanTree while loop ran %d times\n", count);
    // Delete the one remaining list node holding the Huffman tree:
    huffmanTree.root = list.head->tree;
    deleteListNode(&list, list.head);
    return huffmanTree;
}