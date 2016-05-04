#include <stdio.h>
#include <stdlib.h>

#include "BLE.h"
#include "Sample.h"


int main()
{
    double dP0, dN;

    GetBLEData();

    GetLNSData(100.0, &dP0, &dN);

    PrintBLEMean();

    printf("P0  = %.3f  N = %.3f\n", dP0, dN);

    

    printf("\n");
    system("PAUSE");
	return 0;
}


