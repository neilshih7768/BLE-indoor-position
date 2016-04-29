#include <stdio.h>
#include <stdlib.h>
#include "Sample.h"
#include "BLE.h"
#include "MyMath.h"


int main()
{
    const int iSampleRate = 300;
    int i = 0;
    int iData[10][300];
    double dMean[10];
    char sFilePath[30];

    // Sample1();

    // Sample2();

    for(i = 0; i < 10; i++) {
        sprintf(sFilePath, "Bong watch/%dcm.csv", (i+1)*20 ) ;    // 20, 40, ... 200
        LoadData(sFilePath, iData[i]);
    }

    for(i = 0; i < 10; i++) {
        dMean[i] = Mean(iData[i], iSampleRate);
        printf("%d : %f\n", i, dMean[i]);
    }


    
    printf("\n");

    system("PAUSE");
	return 0;
}


