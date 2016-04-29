#include "BLE.h"
#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>


void LoadData(char *sFilePath, int *iData)
{
    FILE *fPtr = NULL;
    char sBuffer[50];
    int i = 0;

    fPtr = fopen(sFilePath, "r");

    if(!fPtr) {
        printf("Open file fail.\n");
        return;
    }

    while (fgets(sBuffer, 50, fPtr) != NULL) {
        iData[i] = atoi(sBuffer);
        i++;
    }

    fclose(fPtr);


}