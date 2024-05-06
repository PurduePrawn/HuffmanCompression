#include "regenTree.h"

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

    // Input tree:
    Tree tree;
    int numLeafs; // Number of unique characters/leafs in the tree, necessary to set length of code table;
    // Regenerate huffman tree from compressed file
    long int postOrderEnd; // Marks the end of the post order traversal in the input file (and the start of actual huffman code)

    tree.root = regenTree(compressedFile, &numLeafs, &postOrderEnd);

    codeTableEntry *codeTable = malloc(numLeafs * sizeof(codeTableEntry));
    // Create code table
    generateCodeTable(tree.root, codeTable);
    // Make new file that turns all huffman codes back into their characters
    decompress(compressedFile, codeTable, argv[2]);
    // Done!
    return EXIT_SUCCESS;
}