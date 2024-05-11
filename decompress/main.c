#include "regenTree.h"
#include "structures.h"
#include "tree.h"
#include "decompress.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

int main(int argc, char **argv)
{
    // Check arg count:
    if (argc != 3)
    {
        perror("Please enter an input and output filename.");
        return EXIT_FAILURE;
    }

    // Input file
    FILE *compressedFile = fopen(argv[1], "rb");
    // Huffman tree:
    Tree tree;
    int numLeafs = 0; // Number of unique characters/leafs in the tree, necessary to set length of code table;
    // Regenerate huffman tree from compressed file
    long int postOrderEnd; // Marks the end of the post order traversal in the input file (and the start of actual huffman code)

    tree.root = regenTree(compressedFile, &numLeafs, &postOrderEnd);

    codeTableEntry *codeTable = malloc(numLeafs * sizeof(codeTableEntry));
    // Create code table
    // generateCodeTable(tree.root, codeTable);
    // printf("CODE TABLE: \n");
    // for (int i = 0; i < numLeafs; i++)
    // {
    //     printf("Char: %c | Code: %s\n", codeTable[i].val, codeTable[i].code);
    // }
    // free(codeTable);
    // // Make new file that turns all huffman codes back into their characters
    FILE *outputFile = fopen(argv[2], "w");
    decompress(compressedFile, outputFile, postOrderEnd, tree.root, 100);
    // Done!
    fclose(compressedFile);
    fclose(outputFile);
    return EXIT_SUCCESS;
}