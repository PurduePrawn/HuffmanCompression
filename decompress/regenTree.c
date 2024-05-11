#include "regenTree.h"
#include "list.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define NUM_BITS_IN_BYTE 8

// Macro for binary byte printing:
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)         \
    ((byte) & 0x80 ? '1' : '0'),     \
        ((byte) & 0x40 ? '1' : '0'), \
        ((byte) & 0x20 ? '1' : '0'), \
        ((byte) & 0x10 ? '1' : '0'), \
        ((byte) & 0x08 ? '1' : '0'), \
        ((byte) & 0x04 ? '1' : '0'), \
        ((byte) & 0x02 ? '1' : '0'), \
        ((byte) & 0x01 ? '1' : '0')

// Using 0 indexing, gets bit from byte at given index and returns it as a 1 or 0
int getBit(Byte byte, int index)
{
    // printf("Getting bit %d from " BYTE_TO_BINARY_PATTERN, index, BYTE_TO_BINARY(byte));
    // printf("\n");
    byte = byte >> (NUM_BITS_IN_BYTE - (index + 1)); // Shift to get 0s followed by all bits in the byte until the one at index
    // printf("The bit is a %d\n", (int)(byte & 0x01));
    return (int)(byte & 0x01);
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
    while (true)
    {

        if (getBit(byte, index) == 1) // Get the bit of the byte at the specified index (0 index -> 1st bit). Check if it is a 1
        {

            c = byte << (index + 1);          // the character contains the bits from byte after the index
            nextByte = fgetc(compressedFile); // and some bits from the beginning of the next byte
            cEnd = nextByte >> (NUM_BITS_IN_BYTE - (index + 1));
            c = c | cEnd; // Add first few digits of next byte to end of c
            printf("Character: %c\n", c);
            // ADD C TO linked list:
            *numLeafs = *numLeafs + 1;
            appendListNode(&subtreeList, createTreeNode(c));
            // printf("Head: %p\nTail: %p\n", subtreeList.head, subtreeList.tail);
            // Increment index because the overlap of the character over the two bytes will naturally increase the index of the next control bit
            byte = nextByte;
            index++;
        }

        else // If a control 0 is found
        {
            if (subtreeList.head == subtreeList.tail)
            {
                TreeNode *finalTree = subtreeList.head->tree;
                deleteListNode(&subtreeList, subtreeList.head);
                displayTree(finalTree, 0);
                printf("%ld\n", ftell(compressedFile));
                *postOrderEnd = ftell(compressedFile);
                return finalTree;
            }
            printf("ZERO\n");
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

    // Must go byte by byte through the file
    // Take the first byte, if its first bit is a 1 (calculate this by shifting right 7):
    // add the next 7 bits and the first bit of the next byte into the byte and add to tree
    // If its first bit is a 0:
    // Look for a one by shifting right less and less until a 1 is seen
}