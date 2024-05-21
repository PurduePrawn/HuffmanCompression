#include "compress.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

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

// Changes control 0s and 1s to bits and writes compressed post order to file
void compressAndWritePostOrder(char *postOrder, int postOrderLength, FILE *file)
{
    int index = 0;          // Where we currently are in the byte (the index marking the start of the portion of the byte still needing to be filled)
    unsigned char byte = 0; // The number that will store current progress on construction of a byte
    unsigned char control;  // Control bit used whenever a 1 is encountered
    unsigned char c;        // Will store any 1's corresponding character

    // For every control bit in the post order array (i increments by 2 for 1s and 1 for 0s):
    for (int i = 0; i < postOrderLength; i += postOrder[i] + 1)
    {

        if (postOrder[i] == 1)
        {
            printf("INDEX: %d ", index);
            printf("\n");
            printf("BYTE: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(byte));
            printf("\n");
            control = 0x80 >> index; // 10000000 (Shift control bit (1) in order to get to that index)
            printf("CONTROL: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(control));
            printf("\n");
            c = postOrder[i + 1]; // 01101001 (example)
            printf("C: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(c));
            printf("\n");
            unsigned char cNew = c >> (index + 1); // 00110100 (shift c to get to the index after the control bit)
            printf("C NEW: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(cNew));
            printf("\n");
            byte = byte | control | cNew; // 10110100 (Add byte, control, and part of the character byte together into a completed byte)
            printf("COMPLETE BYTE: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(byte));
            printf("\n");
            fputc((int)byte, file);                                         // Write the byte to the file
            unsigned char mask = pow(2, index + 1) - 1;                     // 00000001 (Add 1s to the end to access the last 8-(index+1) bits of c)
            unsigned char cEnd = c & mask;                                  // 00000001
            printf("C END: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(cEnd)); // THE REST OF C THAT HAS NOT BEEN COPIED INTO THIS BYTE
            printf("\n");
            printf("\n");
            byte = cEnd << (NUM_BITS_IN_BYTE - (index + 1)); // 10000000 (shift those end elements to the beginning of byte)
            index = index + 1;
        }
        else
        {
            printf("INDEX: %d ", index);
            printf("\n");
            index++; // Byte already has zeros at the end, so just shift the byte index
        }
        if (index == NUM_BITS_IN_BYTE)
        { // If byte is full, write it to file.
            fputc((int)byte, file);
            index = 0;
            byte = 0;
        }
    }
    fputc((char)byte, file); // Write whatever is left in the byte
}
// Function to generate compressed file:
void compress(char *postOrder, long int postOrderLength, codeTableEntry *codeTable, int codeTableLength, char *article, char *filename)
{
    // Open file:
    FILE *fp = fopen(filename, "wb");
    compressAndWritePostOrder(postOrder, postOrderLength, fp);

    long int fileSize = strlen(article);
    fwrite(&fileSize, sizeof(long int), 1, fp);
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
