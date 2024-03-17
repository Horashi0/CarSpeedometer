#include "GPGGA.h"
#include "GPRMC.h"

typedef struct
{
	char	item[20];
}GPS_TEXT_ITEM;

GPS_TEXT_ITEM GpsArray[30];
#define NMEA_BYTE_BUFFER 128

int ResetArray(GPS_TEXT_ITEM gpsArray[30], int *pLoopCount);
int GpggaStructHandler(char sentence[NMEA_BYTE_BUFFER], GPS_TEXT_ITEM gpsArray[30], char tempHexnum[3], int loopCount);
int GprmcStructHandler();
int TypeNmeaString(char sentence[NMEA_BYTE_BUFFER], char *pTypeArray);
bool ValidateNmeaString(char sentence[NMEA_BYTE_BUFFER], char *pHexnum);
int ProcessNmeaString(char sentence[NMEA_BYTE_BUFFER], GPS_TEXT_ITEM gpsArray[30]);
int ReceiveNmeaStrings(char sentence[NMEA_BYTE_BUFFER], int messagePos, GPS_TEXT_ITEM gpsArray[30]);
int ParseNmeaString(char sentence[NMEA_BYTE_BUFFER], GPS_TEXT_ITEM gpsArray[30], char tempHexnum[3], int *pLoopCount);
double CalculateDistance(double lat1, double long1, double lat2, double long2);