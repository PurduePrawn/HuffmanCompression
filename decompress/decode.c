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
    while (!feof(input))
    {
        printf("Starting while loop iteration\n");
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
                printf("char: %c\n", tn->val);
                tn = root;
            }
            Byte mask = pow(2, i);
            printf("MASK: %x\n", mask);
            if (b & mask)
            {
                // GO RIGHT
                tn = tn->right;
                printf("went right\n");
            }
            else
            {
                // GO LEFT
                tn = tn->left;
                printf("went left\n");
            }
        }
        c = fgetc(input);
        printf("Location: %ld\n", ftell(input));
        printf("C is %d\n", (int)c);
    }
}