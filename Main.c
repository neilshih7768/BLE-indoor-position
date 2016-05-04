#include <stdio.h>
#include <stdlib.h>

#include "BLE.h"


int main()
{
    double dP0, dN;

    GetBLEData();

    GetLNSData(100.0, &dP0, &dN);

    PrintBLEMean();

    printf("P0  = %.3f  N = %f.3\n", dP0, dN);
    

    printf("\n");
    system("PAUSE");
	return 0;
}


