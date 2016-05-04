#include "BLE.h"
#include "Matrix.h"
#include "MyMath.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


BLEData bleData[iFileSize];


void LoadFileData(char *sFilePath, BLEData *bleData)
{
    FILE *fPtr = NULL;
    char sBuffer[50];
    int  i = 0;

    fPtr = fopen(sFilePath, "r");

    if(!fPtr) {
        printf("Open file fail.\n");
        return;
    }

    while (fgets(sBuffer, 50, fPtr) != NULL) {
        bleData->iData[i] = atoi(sBuffer);
        i++;
    }

    bleData->dMean = Mean(bleData->iData, iSampleRate);

    fclose(fPtr);
}


void GetBLEData()
{
    int  i = 0;
    char sFilePath[30];

    for(i = 0; i < iFileSize; i++) {
        bleData[i].iDistance = (i+1)*20;        // 20, 40, ... 200
        sprintf(sFilePath, "%s/%dcm.csv", sFolderName, bleData[i].iDistance ) ;    
        LoadFileData(sFilePath, &bleData[i]);
    }
}


void GetLNSData(double dRef, double *dP0, double *dN)
{
    int  i = 0;

    double **mA;        // 1 * iFileSize
    double **mTA;       // iFileSize * 1

    double **mY;        // 1 * iFileSize
    double **mTY;       // iFileSize * 1

    double **mR1;       // iFileSize * iFileSize = mA * mTA
    double **mR2;
    double **mR3;
    double **mR4;

    // Init matrix
    mA = (double **)malloc(sizeof(double));
    mY = (double **)malloc(sizeof(double));

    for(i = 0; i < iFileSize; i++) {
        mA[i]  = (double *)malloc(sizeof(double));
        mY[i]  = (double *)malloc(sizeof(double));
    }

    // Find p0
    for(i = 0; i < iFileSize; i++) {
        bleData[i].dD = (double)bleData[i].iDistance / dRef;
        if(bleData[i].iDistance == (int)dRef)
            *dP0 = bleData[i].dMean;
    }
 
    // Find N
    for(i = 0; i < iFileSize; i++) {
        mA[0][i] = 10 * log10(bleData[i].dD);
    }

    mTA = Transpose(mA, 1, iFileSize);

    for(i = 0; i < iFileSize; i++) {
        mY[0][i] = *dP0 - bleData[i].dMean;
    }

    mTY = Transpose(mY, 1, iFileSize);

    // n = inv(transpose(A) * A) * transpose(A) * y;

    // mA matrix size = 1 * iFileSize
    // mTA matrix size = iFileSize * 1.

    // mR1 = transpose(A) * A 
    // matrix size = 1 * 1.
    mR1 = MultiMatrix(mA, mTA, 1, iFileSize, 1);

    // mR2 = inv(mR1)
    // matrix size = 1 * 1.
    mR2 = Inverse(mR1, 1);

    // mR3 = mR2 * transpose(A) , matrix size = 1 * iFileSize.
    mR3 = MultiMatrix(mR2, mA, 1, 1, iFileSize);
    
    // mR4 = mR3 * y
    mR4 = MultiMatrix(mR3, mTY, 1, iFileSize, 1);

    *dN = mR4[0][0];
}


void PrintBLEMean()
{
    int i = 0;

    for(i = 0; i < iFileSize; i++) {
        printf("%3d : %.3f\n", bleData[i].iDistance, bleData[i].dMean);
    }

    printf("\n");
}



