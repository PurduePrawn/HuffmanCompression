#include "utils.h"
#include "genTree.h"
#include "codeTable.h"
#include "compress.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define ASCII_COUNT 256

int main(int argc, char **argv)
{

    // Check argument count:
    if (argc != 3)
    {
        return EXIT_FAILURE;
    }

    long int counts[ASCII_COUNT] = {0}; // Counts of each character (indexed by its ASCII code)
    countChar(argv[1], counts, ASCII_COUNT);
    printf("There are %ld ds\n", counts[(int)'d']);
    int numDiffChars = 0; // Number of unique characters in the file
    for (int i = 0; i < ASCII_COUNT; i++)
    {
        if (counts[i])
        {
            numDiffChars++;
        }
    }
    printf("There are %d different characters \n", numDiffChars);

    // Preliminary array of character/frequency tree nodes (not a tree) to simply sort them by frequency:
    TreeNode *charFrequencies = calloc(numDiffChars, sizeof(TreeNode));
    int tnIndex = 0;
    for (int countsIndex = 0; countsIndex < ASCII_COUNT; countsIndex++) // Go through 256 elem count array
    {
        if (counts[countsIndex] > 0) // If a character appears in the file
        {
            if (countsIndex == 'H')
            {
                printf("H found %ld times\n", counts[countsIndex]);
            }
            // Add it and its frequency to charFrequencies:
            charFrequencies[tnIndex].character = (char)countsIndex;
            charFrequencies[tnIndex].frequency = counts[countsIndex];
            tnIndex++;
        }
    }

    // Sort array elements by ascending frequency:
    qsort(charFrequencies, numDiffChars, sizeof(TreeNode), cmpfunc /*ascending frequency (see utils.c)*/);
    for (int i = 0; i < numDiffChars; i++)
    {
        printf("%c, %ld\n", charFrequencies[i].character, charFrequencies[i].frequency);
    }
    // Get text from input file:
    char *txt;
    long int txtLength; // LONG INTEGER (for large files)
    readFile(argv[1], &txt, &txtLength);

    // Combine sorted leaf nodes into huffman tree:
    Tree tree = generateHuffmanTree(charFrequencies, numDiffChars);
    displayTree(tree.root, 0);
    printf("Node Count: %d \nLeaf Count: %d\n", tree.nodeCount, tree.leafCount);

    // Allocate enough memory to store a code table:
    codeTableEntry *codeTable = malloc(numDiffChars * sizeof(codeTableEntry)); // Allocate space for code table
    // Generate the code table:
    generateCodeTable(tree.root, codeTable);
    // Code Table:
    for (int i = 0; i < numDiffChars; i++)
    {
        if (codeTable[i].val == '\n')
        {
            printf("/N| %s\n", codeTable[i].code);
        }
        else
        {
            printf("%c | %s\n", codeTable[i].val, codeTable[i].code);
        }
    }

    // Generate post order traversal of binary tree:
    int postOrderLength = tree.nodeCount + tree.leafCount + 1; // Account for control bits and terminating 0
    char *postOrder = generatePostOrder(tree, postOrderLength);
    // Use the code table to compress the article into binary code:
    compress(postOrder, postOrderLength, codeTable, numDiffChars, txt, argv[2]);
    free(postOrder); // Free the post order array
    free(txt);       // Free the article

    // Free all of the code table's memory:
    for (int i = 0; i < numDiffChars; i++)
    {
        free(codeTable[i].code);
    }
    free(codeTable);

    return EXIT_SUCCESS;
}
