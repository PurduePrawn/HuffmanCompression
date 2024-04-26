#include "tree.h"

// Recursive function to generate huffman codes:
void generateCodeEntries(TreeNode *node, codeTableEntry *codeTable, int *index, int iterations, int codeAsDecimal)
{
    // BASE CASE:
    if (!node)
        return;

    // If the current node is a leaf node, add its code string to the code table:
    if (node->character)
    {
        codeTable[*index].val = node->character;
        codeTable[*index].code = malloc(iterations + 1);
        sprintf(codeTable[*index].code, "%0*d", iterations, codeAsDecimal);
        *index = *index + 1;
    }

    // Run the function again for the node's left and right subtrees.
    // Increment iterations and calculate new codeAsDecimal value's according to the direction:
    generateCodeEntries(node->left, codeTable, index, iterations + 1, codeAsDecimal * 10);
    generateCodeEntries(node->right, codeTable, index, iterations + 1, codeAsDecimal * 10 + 1);
}

// Function to generate huffman codes:
void generateCodeTable(TreeNode *node, codeTableEntry *codeTable)
{
    int tableIndex = 0;
    int iterations = 0;
    int codeAsDecimal = 0;
    generateCodeEntries(node, codeTable, &tableIndex, iterations, codeAsDecimal);
}

// Function to write a string of 8 1s and 0s to a file as one byte:
void writeByte(FILE *fp, char *byte)
{
    int num = 0;
    // Convert binary to integer:
    for (int i = 0; i < NUM_BITS_IN_BYTE; i++)
    {
        if (byte[i] == '1')
        {
            num += pow(2, NUM_BITS_IN_BYTE - (i + 1));
        }
    }

    // Add integer (as an 8 bit character) to the file:
    fputc(num, fp);
}

// Function to retrieve a code from the code table:
char *getCode(codeTableEntry *codeTable, int tableLength, char val)
{
    for (int i = 0; i < tableLength; i++)
    {
        if (codeTable[i].val == val)
            return codeTable[i].code;
    }
    return NULL;
}

void addPostOrderEntry(TreeNode *tn, char *postOrder, int *index)
{
    if (tn == NULL)
        return;
    addPostOrderEntry(tn->left, postOrder, index);
    addPostOrderEntry(tn->right, postOrder, index);
    if (tn->character)
    {
        postOrder[*index] = 1; // Add control bit 1 if the character is not null (lead node)
        *index = *index + 1;
    }
    postOrder[*index] = tn->character; // Add the actual character (This would automatically add control bit 0s for null characters)
    *index = *index + 1;
}

char *generatePostOrder(Tree tree, int length)
{
    if (tree.root == NULL)
    {
        return NULL;
    }
    int index = 0;
    char *postOrder = malloc(length * sizeof(char)); // Allocate just enough space to store control bits, characters, and terminating 0:
    addPostOrderEntry(tree.root, postOrder, &index);
    postOrder[index] = 0;
    for (int i = 0; i < index + 1; i++)
    {
        printf("%d ", (int)postOrder[i]);
    }

    return postOrder;
}

// Function to generate compressed file:
void compress(char *postOrder, int postOrderLength, codeTableEntry *codeTable, int codeTableLength, char *article, char *filename)
{
    // Open file:
    FILE *fp = fopen(filename, "wb");
    fwrite(postOrder, sizeof(char), postOrderLength, fp);
    char *code;                            // The huffman code of a character in the article
    char byte[NUM_BITS_IN_BYTE + 1] = {0}; // An array (with a terminating null character) that will be filled with "bits" and written to the output file

    // For every character in the article
    for (int i = 0; i < strlen(article); i++)
    {
        code = getCode(codeTable, codeTableLength, article[i]); // Get code for this character

        // Until all the code has been copied:
        while (strlen(code) > 0)
        {
            // Find how much can be copied into the byte:
            int availableLength = NUM_BITS_IN_BYTE - strlen(byte);
            int bitsToCopy = (strlen(code) < availableLength) ? strlen(code) : availableLength;

            // Copy as much of code as possible into the byte array:
            memcpy(&byte[strlen(byte)], code, bitsToCopy);

            // If byte has been filled, add it to the file and reset it:
            if (strlen(byte) == NUM_BITS_IN_BYTE)
            {
                writeByte(fp, byte);
                memset(byte, 0, NUM_BITS_IN_BYTE); // Reset the byte to null characters
            }

            code = &code[bitsToCopy]; // Update code to only point to the portion of the code that has not been copied
        }
    }
    // Write any remaining bits followed by 0s (to complete a byte) to the file:
    writeByte(fp, byte);

    // Close file:
    fclose(fp);
}