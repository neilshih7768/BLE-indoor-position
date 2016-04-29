// Reference page : Inverse of a square matrix
// https://www.cs.rochester.edu/~brown/Crypto/assts/projects/adj.html

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"


int main()
{
    const int size    = 3;
    double mTestInit[3][3] = { {1, 2, 0}, { -1, 1, 1}, { 1, 2, 3} };
    
    double **mTest    = (double **)malloc(sizeof(double) * size);
    double **mInverse = (double **)malloc(sizeof(double) * size);
    double **mMulti   = (double **)malloc(sizeof(double) * size);
    int i = 0, j = 0;

    for(i = 0; i < size; i++) {
        mTest[i]      = (double *)malloc(sizeof(double) * size);
        mInverse[i]   = (double *)malloc(sizeof(double) * size);
        mMulti[i]     = (double *)malloc(sizeof(double) * size);
    }

    

    for(i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            mTest[i][j] = mTestInit[i][j];
        }
    }

    // Test matrix
    printf("Test matrix = \n");
    PrintMatrix(mTest, size, size);

    
    Inverse(mTest, size, mInverse);
    printf("Inverse matrix = \n");
    PrintMatrix(mInverse, size, size);


    MultiMatrix(mTest, mInverse, 3, 3, 3, mMulti);
    printf("Multiple matrix = \n");
    PrintMatrix(mMulti, size, size);
    
    // Free memory
    for(i = 0; i < size; i++) {
        free(mTest[i]);
        free(mInverse[i]);
    }

    free(mTest);
    free(mInverse);

    system("PAUSE");
	return 0;
}


