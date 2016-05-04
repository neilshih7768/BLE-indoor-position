#include "Sample.h"
#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>


// Find a inverse matrix of a square and check it
void Sample1()
{
    const int iSize   = 3;
    double mTestInit[3][3] = { {1, 2, 0}, { -1, 1, 1}, { 1, 2, 3} };
    
    double **mTest    = (double **)malloc(sizeof(double) * iSize);
    double **mInverse;
    double **mMulti   = (double **)malloc(sizeof(double) * iSize);

    int i = 0, j = 0;

    for(i = 0; i < iSize; i++) {
        mTest[i]      = (double *)malloc(sizeof(double) * iSize);
        mMulti[i]     = (double *)malloc(sizeof(double) * iSize);
    }

    for(i = 0; i < iSize; i++) {
        for(j = 0; j < iSize; j++) {
            mTest[i][j] = mTestInit[i][j];
        }
    }

    printf("\n======Sample 1 ======\n");

    // Print input matrix
    printf("Test matrix A = \n");
    PrintMatrix(mTest, iSize, iSize);


    // Inverse the matrix
    mInverse = Inverse(mTest, iSize);
    printf("Inverse matrix IA = \n");
    PrintMatrix(mInverse, iSize, iSize);


    // Check the inverse matrix multiplied by input matrix is identity matrix
    mMulti = MultiMatrix(mTest, mInverse, 3, 3, 3);
    printf("Multiple matrix A * IA = \n");
    PrintMatrix(mMulti, iSize, iSize);
    
    // Free memory
    for(i = 0; i < iSize; i++) {
        free(mTest[i]);
        free(mInverse[i]);
    }

    free(mTest);
    free(mInverse);
}


// Find a transpose matrix of a none square matrix
void Sample2()
{
    const int iSizeM    = 2, iSizeN = 3;
    double mTestInit[2][3] = { {1, 2, 0}, { -1, 1, 1} };

    double **mTest      = (double **)malloc(sizeof(double) * iSizeM); // Important index is M
    double **mTranspose = (double **)malloc(sizeof(double) * iSizeN);

    int i = 0, j = 0;

    for(i = 0; i < iSizeM; i++) {                                   // Important index is M
        mTest[i]        = (double *)malloc(sizeof(double) * iSizeN);  // Important index is N
    }

    for(i = 0; i < iSizeN; i++) {
        mTranspose[i]   = (double *)malloc(sizeof(double) * iSizeM);
    }

    for(i = 0; i < iSizeM; i++) {
        for(j = 0; j < iSizeN; j++) {
            mTest[i][j] = mTestInit[i][j];
        }
    }

    printf("\n======Sample 2 ======\n");

    // Print input matrix
    printf("Test matrix A = \n");
    PrintMatrix(mTest, iSizeM, iSizeN);


    // Transpose the matrix
    mTranspose = Transpose(mTest, iSizeM, iSizeN);
    printf("Transpose matrix TA = \n");
    PrintMatrix(mTranspose, iSizeN, iSizeM);

    for(i = 0; i < iSizeM; i++) {
        free(mTest[i]);
    }

    for(i = 0; i < iSizeN; i++) {
        free(mTranspose[i]);
    }

    free(mTest);
    free(mTranspose);
}