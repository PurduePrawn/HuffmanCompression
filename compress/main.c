#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "tree.h"

#define ASCII_COUNT 256

// Allocate memory for a string and add all characters in the file into the string plus a null character:
void readFile(char *filename, char **arr, int *length)
{
    FILE *fp = fopen(filename, "r");

    // Find size of file:
    fseek(fp, 0, SEEK_END);
    long int size = ftell(fp);
    *length = size / sizeof(char);

    // Allocate memory plus space for null character:
    *arr = malloc(size + sizeof(char));

    // Copy contents of file into array:
    fseek(fp, 0, SEEK_SET);
    fread(*arr, sizeof(char), size / sizeof(char), fp);

    // Add null character to end of allocated memory
    *(*arr + size) = '\0';

    fclose(fp);
}

bool countChar(char *filename, int *counts, int size)
{
    // open a file whose name is filename for reading
    FILE *fp = fopen(filename, "r");
    // if fopen fails, return false. Do NOT fclose
    if (fp == NULL)
    {
        return false;
    }
    // if fopen succeeds, read every character from the file
    //
    // if a character (call it onechar) is between
    // 0 and size - 1 (inclusive), increase
    // counts[onechar] by one
    // You should *NOT* assume that size is 256
    // reemember to call fclose
    // you may assume that counts already initialized to zero
    // size is the size of counts
    // you may assume that counts has enough memory space
    //
    // hint: use fgetc
    // Please read the document of fgetc carefully, in particular
    // when reaching the end of the file
    //

    int onechar; // Character ASCII value serving as an index for counts[]
    do
    {
        onechar = fgetc(fp);
        if (0 <= onechar && onechar <= size - 1)
        {
            counts[onechar]++;
        }
    } while (onechar != EOF);
    fclose(fp);
    return true;
}

// Takes the FREQUENCY part (which is right next to its character) of eeach character and compares them:
int cmpfunc(const void *a, const void *b)
{
    return ((*((int *)a + 1)) - *((int *)b + 1));
}

int main(int argc, char **argv)
{

    // Check argument count:
    if (argc != 3)
    {
        return EXIT_FAILURE;
    }
    int counts[ASCII_COUNT] = {0};
    countChar(argv[1], counts, ASCII_COUNT);
    int numDiffChars = 0;
    for (int i = 0; i < ASCII_COUNT; i++)
    {
        if (counts[i])
        {
            numDiffChars++;
        }
    }

    // 2d array to store character ASCIIs and their corresponding frequencies in the file (<char>, <frequency>):
    int *charFrequencies = malloc(2 * numDiffChars * sizeof(int));
    int j = 0;
    for (int i = 0; i < ASCII_COUNT; i++)
    {
        if (counts[i])
        {
            charFrequencies[j++] = i;
            charFrequencies[j++] = counts[i];
        }
    }

    // for (j = 0; j < numDiffChars; j++)
    // {
    //     printf("%c: %d\n", charFrequencies[j * 2], charFrequencies[j * 2 + 1]);
    // }
    qsort(charFrequencies, numDiffChars, sizeof(int) * 2, cmpfunc);
    // for (j = 0; j < numDiffChars; j++)
    // {
    //     printf("%c: %d\n", charFrequencies[j * 2], charFrequencies[j * 2 + 1]);
    // }

    // Get end of article from input file:
    char *article;
    int articleLength;
    readFile(argv[1], &article, &articleLength);

    // Allocate stack memory to store the root of a tree:
    Tree tree;
    int numTreeNodes = 0;
    // Generate a tree in the heap from the post order traversal and assign the root's address to tree.root:
    tree.root = generateHuffmanTree(charFrequencies, 2 * numDiffChars, &numTreeNodes);
#ifdef TREE
    displayTree(tree.root, 1);
    tree.root = deleteTree(tree.root);
    return EXIT_SUCCESS;
#endif

    // Allocate enough memory to store a code table:
    codeTableEntry *codeTable = malloc(numDiffChars * sizeof(codeTableEntry)); // Allocate space for code table
    // Generate the code table:
    generateCodeTable(tree.root, codeTable);

    // Generate post order traversal of binary tree:
    int postOrderLength = numTreeNodes + numDiffChars + 1; // Account for control bits and terminating 0
    char *postOrder = generatePostOrder(tree, postOrderLength);

    // Use the code table to compress the article into binary code:
    compress(postOrder, postOrderLength, codeTable, numDiffChars, article, argv[2]);

    free(postOrder); // Free the post order array
    free(article);   // Free the article

    // Free all of the code table's memory:
    for (int i = 0; i < numDiffChars; i++)
    {
        free(codeTable[i].code);
    }
    free(codeTable);

    tree.root = deleteTree(tree.root); // Delete the tree
    return EXIT_SUCCESS;
}
