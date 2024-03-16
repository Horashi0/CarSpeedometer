typedef struct
{
	char	item[20];
}GPS_TEXT_ITEM;

GPS_TEXT_ITEM GpsArray[30];

void GpggaStructHandler();
void GprmcStructHandler();
bool ValidateNmeaString();
void ProcessNmeaString();
void ReceiveNmeaStrings();
double CalculateDistance(double lat1, double long1, double lat2, double long2);