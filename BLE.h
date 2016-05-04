#ifndef BLE_H
#define BLE_H


#define  iFileSize    10
#define  iSampleRate  300

const static char *sFolderName = "Bong watch";

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