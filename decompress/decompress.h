#include <stdio.h>
#include "structures.h"
void decompress(FILE *input, FILE *output, long int postOrderEnd, TreeNode *root, long int numChars);