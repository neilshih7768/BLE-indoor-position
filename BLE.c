#include "BLE.h"
#include "Matrix.h"
#include "MyMath.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


BLEData bleData[iFileSize];
double **mA;        // iFileSize * 1
double **mTA;       // 1 * iFileSize
double **mY;        // 1 * iFileSize

double **mR1;       // iFileSize * iFileSize = mA * mTA


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

void InitMatrix()
{
    int i = 0, j = 0;

    for(i = 0; i < iFileSize; i++) {
        mA  = (double **)malloc(sizeof(double) * iFileSize);
        mTA = (double **)malloc(sizeof(double) * 1);
        mY  = (double **)malloc(sizeof(double) * 1);

        mR1 = (double **)malloc(sizeof(double) * 1); 

        for(j = 0; j < iFileSize; j++) {
            mA[j]  = (double *)malloc(sizeof(double) * 1);
            mR1[j] = (double *)malloc(sizeof(double) * 1);
        }
        mTA[0] = (double *)malloc(sizeof(double) * iFileSize);
        mY[0]  = (double *)malloc(sizeof(double) * iFileSize);
    }
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

    // Find p0
    for(i = 0; i < iFileSize; i++) {
        bleData[i].dD = (double)bleData[i].iDistance / dRef;
        if(bleData[i].iDistance == (int)dRef)
            *dP0 = bleData[i].dMean;
    }
 
    // Find N
    InitMatrix();

    for(i = 0; i < iFileSize; i++) {
        *mA[i] = 10 * log10(bleData[i].dD);
    }

    Transpose(mA, iFileSize, 1, mTA);

    for(i = 0; i < iFileSize; i++) {
        mY[0][i] = *dP0 - bleData[i].dMean;
    }

    //MultiMatrix(mA, mTA, iFileSize, 1, iFileSize, mR1);
}


void PrintBLEMean()
{
    int i = 0;

    for(i = 0; i < iFileSize; i++) {
        printf("%3d : %.3f\n", bleData[i].iDistance, bleData[i].dMean);
    }

    printf("\n");
}



