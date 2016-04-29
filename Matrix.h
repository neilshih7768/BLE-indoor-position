// Written by Neil Shih in FTDI
// Date : 2016 / 4 / 28
// Reference page : Inverse of a square matrix
// https://www.cs.rochester.edu/~brown/Crypto/assts/projects/adj.html

#ifndef MATRIX_H
#define MATRIX_H


/*
Matrix example :
    matrixA = {
        {1, 2, 3}
        {4, 5, 6}
    }

    matrixA is a 2 * 3 (M * N) matrix
    row size is 2 (M)
    column size is 3 (N)
*/


// Find the inverse matrix(mOutput) of a matrix(mInput) with row size(iSize)
// Inverse = Transpose( CoFactor ) / Determinant
void Inverse(double **mInput, int iSize, double **mOutput);


// Find the cofactor matrix(mOutput) of a square matrix(mInput) with row size(iSize)
void CoFactor(double **mInput, int iSize, double **mOutput);


// Find the transpose matrix(mOutput) of a matrix(mInput) with row size(iSizeM) and column size(iSizeN)
void Transpose(double **mInput, int iSizeM, int iSizeN, double **mOutput);


// Find the transpose matrix(mOutput) of a matrix(mInput) with row size(iSize)
void TransposeSquare(double **mInput, int iSize, double **mOutput);


// Recursive definition of determinate using expansion by minors
double Determinant(double **mInput, int size);


// Find the multiplication(mOutput) of matrixA(mInputA) and matrixB(mInputB)
// matrixA is a iSizeM * iSizeN matrix
// matrixB is a iSizeN * iSizeO matrix
// mOutput is a iSizeM * iSizeM matrix
void MultiMatrix(double **mInputA, double **mInputB, int iSizeM, int iSizeN, int iSizeO, double **mOutput);


// Find the multiplication(mOutput) of square matrixA(mInputA) and square matrixB(mInputB)
// matrixA, matrixB and mOutput are a iSize * iSize matrix
void MultiSquareMatrix(double **mInputA, double **mInputB, int iSize, double **mOutput);


// Print the data of a matrix(mInput) with row size(iSizeM) and column size(iSizeN)
void PrintMatrix(double **mInput, int iSizeM, int iSizeN);


// Print the data of a square matrix(mInput) with size(iSize)
void PrintSquareMatrix(double **mInput, int iSize);


#endif