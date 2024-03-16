typedef struct
{
	char	item[20];
}GPS_TEXT_ITEM;

GPS_TEXT_ITEM GpsArray[30];

int GpggaStructHandler();
int GprmcStructHandler();
bool ValidateNmeaString();
int ProcessNmeaString();
int ReceiveNmeaStrings();
int ParseNmeaString();
double CalculateDistance(double lat1, double long1, double lat2, double long2);