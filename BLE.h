#ifndef BLE_H
#define BLE_H


#define iFileSize     18
#define iSampleHeader 8      // How many headers in data
#define iSampleRate   1000

// const static char *sFolderName = "Bong watch";
const static char *sFolderName = "04-11-cloudy";

typedef struct _BLEData {
    int iDistance;              // CM
    int iData[iSampleRate];     // RSSIs
    double dMean;               // RSSIs mean
    double dD;
} BLEData;


void GetBLEData();
void GetLNSData(double dRef, double *dP0, double *dN);
void PrintBLEMean();


#endif