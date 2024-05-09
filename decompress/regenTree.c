#include "regenTree.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define NUM_BITS_IN_BYTE 8

// Using 0 indexing, gets bit from byte at given index and returns it as a 1 or 0
int getBit(Byte byte, int index)
{
    byte >> (NUM_BITS_IN_BYTE - (index + 1)); // Shift to get 0s followed by all bits in the byte until the one at index
    return byte % 2;                          // Access last bit of shifted byte
}

TreeNode *regenTree(FILE *compressedFile, int *numLeafs, long int *postOrderEnd)
{
    List subtreeList = {0};            // Linked list to build huffman tree
    int index = 0;                     // Index to keep track of how many bits have been read from the current byte in question
    Byte byte = fgetc(compressedFile); // Byte that will hold bytes in the post order
    Byte nextByte;
    Byte c; // The character that will be filled and added to the tree
    Byte cEnd;
    TreeNode *subtree;
    // While the list doesn't have one element:
    while (subtreeList.head != subtreeList.tail || subtreeList.head == NULL)
    {

        if (getBit(byte, index) == 1) // Get the bit of the byte at the specified index (0 index -> 1st bit). Check if it is a 1
        {
            c = byte << (index + 1);          // the character contains the bits from byte after the index
            nextByte = fgetc(compressedFile); // and some bits from the beginning of the next byte
            cEnd = nextByte >> (NUM_BITS_IN_BYTE - (index + 1));
            c = c | cEnd; // Add first few digits of next byte to end of c

            // ADD C TO linked list:
            appendListNode(&subtreeList, createTreeNode(c));
            // Increment index because the overlap of the character over the two bytes will naturally increase the index of the next control bit
            byte = nextByte;
            index++;
        }
        else // If a control 0 is found
        {
            // Combine last 2 list nodes into one
            subtree = createTreeNode(0);                  // To hold last 2 list nodes
            subtree->left = subtreeList.tail->prev->tree; // Second to last list node
            subtree->right = subtreeList.tail->tree;      // Last list node

            // Replace last two list nodes with subtree
            deleteListNode(&subtreeList, subtreeList.tail->prev);
            deleteListNode(&subtreeList, subtreeList.tail);
            appendListNode(&subtreeList, subtree);

            // Increment index (If this makes it 8, this will be fixed below)
            index++;
        }
        if (index == 8) // Current byte has been fully processed
        {
            index = 0;
            byte = fgetc(compressedFile);
        }
    }

    TreeNode *finalTree = subtreeList.head->tree;
    deleteListNode(&subtreeList, subtreeList.head);
    return finalTree;

    // Must go byte by byte through the file
    // Take the first byte, if its first bit is a 1 (calculate this by shifting right 7):
    // add the next 7 bits and the first bit of the next byte into the byte and add to tree
    // If its first bit is a 0:
    // Look for a one by shifting right less and less until a 1 is seen
}