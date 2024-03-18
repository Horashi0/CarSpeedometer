#include "GPGGA.h"
#include "GPRMC.h"

typedef struct
{
	char	item[20];
}GPS_TEXT_ITEM;

GPS_TEXT_ITEM GpsArray[30];
#define NMEA_BYTE_BUFFER 128

int ResetArray(GPS_TEXT_ITEM gpsArray[30], int *pLoopCount);
int GpggaStructHandler(char sentence[NMEA_BYTE_BUFFER], GPS_TEXT_ITEM gpsArray[30], char tempHexnum[3], int loopCount, GPGGA *gpggaStruct);
int GprmcStructHandler();
int TypeNmeaString(char sentence[NMEA_BYTE_BUFFER], char *pTypeArray);
bool ValidateNmeaString(char sentence[NMEA_BYTE_BUFFER], char *pHexnum);
int ProcessNmeaString(char sentence[NMEA_BYTE_BUFFER], GPS_TEXT_ITEM gpsArray[30], GPGGA *gpggaStruct);
int ReceiveNmeaStrings(char sentence[NMEA_BYTE_BUFFER], int messagePos, GPS_TEXT_ITEM gpsArray[30], GPGGA *GpggaStruct);
int ParseNmeaString(char sentence[NMEA_BYTE_BUFFER], GPS_TEXT_ITEM gpsArray[30], char tempHexnum[3], int *pLoopCount);
double CalculateDistance(double lat1, double long1, double lat2, double long2);
int ConvertDecimalDegrees(float Latitude, float Longitude, char NorthSouth[1], char EastWest[1], float *pLatitude, float *pLongitude);