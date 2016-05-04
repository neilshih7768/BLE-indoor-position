#include <stdio.h>
#include <stdlib.h>

#include "BLE.h"
#include "Sample.h"


int main()
{
    double dP0, dN, dRef;

    dRef = 200.0;

    GetBLEData();

    GetLNSData(dRef, &dP0, &dN);

    PrintBLEMean();

    printf("P0  = %.3f  N = %.3f dRef = %.3f \n", dP0, dN, dRef);

    printf("\n");
    system("PAUSE");
	return 0;
}


