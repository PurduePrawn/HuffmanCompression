#include "regenTree.h"
// Allocates and initialize tree node with value val:
TreeNode *createTreeNode(char val)
{
    TreeNode *tn = malloc(sizeof(TreeNode));
    tn->left = NULL;
    tn->right = NULL;
    tn->val = val;
    return tn;
}

int getBit(Byte byte, int index)
{
    byte >> (NUM_BITS_IN_BYTE - (index + 1)); // Shift to get 0s followed by all bits in the byte until the one at index
    return byte % 2;                          // Access last bit of shifted byte
}
TreeNode *regenTree(FILE *compressedFile, int *numLeafs, long int *postOrderEnd)
{
    int index = 0;
    Byte byte = fgetc(compressedFile);
    Byte c; // The character that will be filled and added to the tree
    int done;
    while (!done)
    {

        if (getBit(byte, index) == 1)
        {
            c = byte << (index + 1);
            byte = fgetc(compressedFile);
            c = c | (byte >> NUM_BITS_IN_BYTE - (index + 1)); // Add first few digits of next byte to end of c
            // ADD C TO FILE!
            TreeNode *subTree = createTreeNode(c);
            index++;
        }
        else
        {
            // Combine last 2 list nodes into one
            index++;
        }
    }
    // Must go byte by byte through the file
    // Take the first byte, if its first bit is a 1 (calculate this by shifting right 7):
    // add the next 7 bits and the first bit of the next byte into the byte and add to tree
    // If its first bit is a 0:
    // Look for a one by shifting right less and less until a 1 is seen
}