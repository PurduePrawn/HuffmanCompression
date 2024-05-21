#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "structures.h"
typedef unsigned char Byte;
void decode(FILE *input, FILE *output, long int postOrderEnd, TreeNode *root)
{
    fseek(input, postOrderEnd, SEEK_SET);
    printf("END: %d\n", (int)postOrderEnd);
    long int numChars;
    fread(&numChars, sizeof(long int), 1, input);
    char c = fgetc(input);
    Byte b;
    TreeNode *tn = root;
    long int count = 0;
    while (c != EOF)
    {
        b = c;
        // printf("BYTE: %x\n", b);
        for (int i = 7; i >= 0; i--)
        {
            if (count >= numChars)
            {
                return;
            }
            if (!(tn->right) && !(tn->left)) // if leaf
            {
                count++;
                fputc(tn->val, output);
                // printf("%c", tn->val);
                tn = root;
            }
            Byte mask = pow(2, i);
            // printf("MASK: %x\n", mask);
            if (b & mask)
            {
                // GO RIGHT
                tn = tn->right;
            }
            else
            {
                // GO LEFT
                tn = tn->left;
            }
        }
        c = fgetc(input);
    }
}