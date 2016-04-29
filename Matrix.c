#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Matrix.h"
#include <string.h>


// Find the inverse matrix(mOutput) of a matrix(mInput) with row size(iSize)
// Inverse = TransposeSquare( CoFactor ) / Determinant
void Inverse(double **mInput, int iSize, double **mOutput)
{
    double **dTranspose = (double **)malloc(sizeof(double) * iSize);
    double **dCoFactor  = (double **)malloc(sizeof(double) * iSize);
    double dDeterminant = Determinant(mInput, iSize);
    int i = 0, j = 0;

    for(i = 0; i < iSize; i++) {
        dTranspose[i]   = (double *)malloc(sizeof(double) * iSize);
        dCoFactor[i]    = (double *)malloc(sizeof(double) * iSize);
    }

    CoFactor(mInput, iSize, dCoFactor);
    TransposeSquare(dCoFactor, iSize, dTranspose);

    for(i = 0; i < iSize; i++) {
        for(j = 0; j < iSize; j++) {
            mOutput[i][j] = dTranspose[i][j] / dDeterminant;
        }
    }

    for(i = 0; i < iSize; i++) {
        free(dTranspose[i]);
        free(dCoFactor[i]);
    }

    free(dTranspose);
    free(dCoFactor);

    return;
}


// Find the cofactor matrix(mOutput) of a square matrix(mInput) with row size(iSize)
void CoFactor(double **mInput, int iSize, double **mOutput)
{
   int i, j, ii, jj, i1, j1;
   double det;
   double **c;

   c = (double**)malloc((iSize-1) * sizeof(double *));
   for (i = 0; i < iSize-1; i++)
     c[i] = (double*)malloc((iSize-1) * sizeof(double));

   for (j = 0; j < iSize; j++) {
      for (i = 0; i < iSize; i++) {

         // Form the adjoint a_ij
         i1 = 0;
         for (ii = 0; ii < iSize; ii++) {
            if (ii == i)
               continue;
            j1 = 0;
            for (jj = 0; jj < iSize; jj++) {
               if (jj == j)
                  continue;
               c[i1][j1] = mInput[ii][jj];
               j1++;
            }
            i1++;
         }

         // Calculate the determinate
         det = Determinant(c, iSize-1);

         // Fill in the elements of the cofactor
         mOutput[i][j] = pow(-1.0, i+j+2.0) * det;
      }
   }
   for (i = 0; i < iSize-1; i++) {
      free(c[i]);
   }
   free(c);
}


// Transpose of a matrix(mInput) with row size(iSizeM) and column size(iSizeN)
void Transpose(double **mInput, int iSizeM, int iSizeN, double **mOutput)
{
    int i = 0, j = 0;

    for(i =  0; i < iSizeM; i++)
        for(j = 0; j < iSizeN; j++)
            mOutput[j][i] = mInput[i][j];
}


// TransposeSquare of a square matrix(mInput) with row size(iSize)
void TransposeSquare(double **mInput, int iSize, double **mOutput)
{
    Transpose(mInput, iSize, iSize, mOutput);
}


// Recursive definition of determinate using expansion by minors
double Determinant(double **mInput,int iSize)
{
   int i, j, j1, j2;
   double det = 0;
   double **m = NULL;

   if (iSize < 1) {          // Error

   } else if (iSize == 1) {  // Shouldn't get used
      det = mInput[0][0];
   } else if (iSize == 2) {
      det = mInput[0][0] * mInput[1][1] - mInput[1][0] * mInput[0][1];
   } else {
      det = 0;
      for (j1 = 0; j1 < iSize; j1++) {
         m = (double**)malloc((iSize-1)*sizeof(double *));
         for (i = 0; i < iSize-1; i++)
            m[i] = (double*)malloc((iSize-1)*sizeof(double));
         for (i = 1 ; i < iSize; i++) {
            j2 = 0;
            for (j = 0; j < iSize; j++) {
               if (j == j1)
                  continue;
               m[i-1][j2] = mInput[i][j];
               j2++;
            }
         }
         det += pow(-1.0, j1+2.0) * mInput[0][j1] * Determinant(m, iSize-1);
         for (i = 0; i < iSize-1; i++) {
            free(m[i]);
         }
         free(m);
      }
   }

   return(det);
}


// Find the product(mOutput) of matrixA(mInputA) and matrixB(mInputB)
// matrixA is a iSizeM * iSizeN matrix
// matrixB is a iSizeN * iSizeO matrix 
// mOutput is a iSizeM * iSizeM matrix
void MultiMatrix(double **mInputA, double **mInputB, int iSizeM, int iSizeN, int iSizeO, double **mOutput)
{
    int i = 0, j = 0, k = 0;
    for(i = 0; i < iSizeM; i++) {
        for(j = 0; j < iSizeO; j++) {
            double sum = 0;
            for(k = 0; k < iSizeN; k++) {
                sum += mInputA[i][k] * mInputB[k][j];
                //printf("%2.2f * %2.2f = %2.2f\n", mInputA[i][k], mInputB[k][j], mInputA[i][k] * mInputB[k][j]);
            }
            //printf("[%d][%d] = %2.2f\n", i, j, sum);
            mOutput[i][j] = sum;
        }
    }
}


// Find the product(mOutput) of square matrixA(mInputA) and square matrixB(mInputB)
// matrixA, matrixB and mOutput are a iSizeM * iSizeM matrix
void MultiSquareMatrix(double **mInputA, double **mInputB, int iSize, double **mOutput)
{
    MultiMatrix(mInputA, mInputB, iSize, iSize, iSize, mOutput);
}


// Print the data of matrix(mInput) with row size(iSizeM) and column size(iSizeN)
void PrintMatrix(double **mInput, int iSizeM, int iSizeN)
{
    int i = 0, j = 0;
    for(i = 0; i < iSizeM; i++) {
        for(j = 0; j < iSizeN; j++) {
            if(-0 == mInput[i][j])      // Strang condition
                mInput[i][j] = 0;

            if(0 <= mInput[i][j])       // For align
                printf(" ");

            printf("%3.3f ", mInput[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}


// Print the data of a square matrix(mInput) with size(iSize)
void PrintSquareMatrix(double **mInput, int iSize)
{
    PrintMatrix(mInput, iSize, iSize);
}