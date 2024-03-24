#include <Arduino.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <ncurses.h>

#include "main.hpp"
#include "GPGGA.h"
#include "GPRMC.h"

const byte rxPin = 4;
const byte txPin = 5;

LiquidCrystal lcd(9, 10, 11, 12, 13, 14);

char Sentence[NMEA_BYTE_BUFFER];
int MessagePos = 0;

GPGGA *GpggaStruct = (GPGGA*)GpsArray[25].item;
GPRMC *GprmcStruct;

void setup() {
	Serial.begin(9600);
	lcd.begin(16,2);

	pinMode(rxPin, INPUT);
	pinMode(txPin, OUTPUT);
	Serial2.begin(9600,SERIAL_8N1, rxPin, txPin, false);
}

void loop() {
	delay(1000);
	ReceiveNmeaStrings(Sentence, MessagePos, GpsArray, GpggaStruct);

	//DebugPrintout(GpggaStruct);
}

int DebugPrintout(GPGGA* gpggaStruct) {
	char charVelocity[6], latitude[10], longitude[10], previousLatitude[10], previousLongitude[10];

	/*dtostrf(gpggaStruct->Velocity, sizeof(charVelocity) - 1, 0, charVelocity);
	dtostrf((double)gpggaStruct->DecimalDegreesLatitude, sizeof(latitude) - 1, 4, latitude);
	dtostrf((double)gpggaStruct->DecimalDegreesLongitude, sizeof(longitude) - 1, 4, longitude);
	dtostrf((double)gpggaStruct->PreviousDecimalDegreesLatitude, sizeof(previousLatitude) - 1, 4, previousLatitude);
	dtostrf((double)gpggaStruct->PreviousDecimalDegreesLongitude, sizeof(previousLongitude) - 1, 4, previousLongitude);*/

	//printf("Sentence: %s\n", gpggaStruct->Sentence);
	//printf("Time: %s:  Lat %s:  Long %s:  Velocity: %s\n\n", gpggaStruct->UtcTime, latitude, longitude, charVelocity);

	
	
	return 0;
}

int GpggaStructHandler(char sentence[NMEA_BYTE_BUFFER], GPS_TEXT_ITEM gpsArray[30], char tempHexnum[3], int loopCount, GPGGA* gpggaStruct) {
	//char* placeholder;

	//strncpy(gpggaStruct->Sentence, sentence, sizeof(gpggaStruct->Sentence));
	/*gpggaStruct->PreviousDecimalDegreesLatitude = gpggaStruct->DecimalDegreesLatitude;
	gpggaStruct->PreviousDecimalDegreesLongitude = gpggaStruct->DecimalDegreesLongitude;*/

	ParseNmeaString(sentence, gpsArray, tempHexnum, &loopCount);

	int hours, mins, secs, integerPlaceholder; // Placeholder for integer conversion
	float floatPlaceholder = 0, pLatitude, pLongitude; // Placeholder for float conversion
	char time[10], timePlaceholder[10]; // Holds string of formatted time, Placeholder string for time
	  

	strncpy(gpggaStruct->Id, gpsArray[0].item, sizeof(gpggaStruct->Id)); 

	strncpy(gpggaStruct->UtcTime, gpsArray[1].item, sizeof(gpggaStruct->UtcTime));
	int items = sscanf(gpsArray[1].item, "%02u%02u%02u", (unsigned int*)&hours, (unsigned int*)&mins, (unsigned int*)&secs);
	if (items == 3) {
		sprintf(time, "%d", hours);

		sprintf(timePlaceholder, ":%d", mins);
		strncat(time, timePlaceholder, strlen(timePlaceholder));
		memset(timePlaceholder, 0, 8);

		sprintf(timePlaceholder, ":%d", secs);
		strncat(time, timePlaceholder, strlen(timePlaceholder));

		strncpy(gpggaStruct->UtcTime, time, sizeof(gpggaStruct->UtcTime));
	}
	
	pLatitude = strtod(gpsArray[2].item, NULL);
	gpggaStruct->Latitude = pLatitude;

	strncpy(gpggaStruct->NorthSouth, gpsArray[3].item, sizeof(gpggaStruct->NorthSouth));
	
	pLongitude = strtod(gpsArray[4].item, NULL);
	gpggaStruct->Longitude = pLongitude;	

	strncpy(gpggaStruct->EastWest, gpsArray[5].item, sizeof(gpggaStruct->EastWest));
	strncpy(gpggaStruct->FixedField1, gpsArray[10].item, sizeof(gpggaStruct->FixedField1));
	strncpy(gpggaStruct->FixedField2, gpsArray[12].item, sizeof(gpggaStruct->FixedField2));
	strncpy(gpggaStruct->DgpsAge, gpsArray[13].item, sizeof(gpggaStruct->DgpsAge));
	strncpy(gpggaStruct->DgpsStationID, gpsArray[14].item, sizeof(gpggaStruct->DgpsStationID));
	strncpy(gpggaStruct->CheckSum, gpsArray[15].item, sizeof(gpggaStruct->CheckSum));
	
	//Integer conversion then assignment to Structure member
	sscanf(gpsArray[6].item, "%d", &integerPlaceholder);
	gpggaStruct->FixStatus = integerPlaceholder;

	sscanf(gpsArray[7].item, "%d", &integerPlaceholder);
	gpggaStruct->Nos = integerPlaceholder;

	sscanf(gpsArray[8].item, "%f", &floatPlaceholder);
	gpggaStruct->Hdop = floatPlaceholder;
	

	sscanf(gpsArray[9].item, "%f", &floatPlaceholder);
	gpggaStruct->Altitude = floatPlaceholder;

	sscanf(gpsArray[11].item, "%f", &floatPlaceholder);
	gpggaStruct->GeoID = floatPlaceholder;

	//ConvertDecimalDegrees(gpggaStruct->Latitude, gpggaStruct->Longitude, gpggaStruct->NorthSouth, gpggaStruct->EastWest, &pLatitude, &pLongitude);
	
	//gpggaStruct->DecimalDegreesLatitude = pLatitude;
	//gpggaStruct->DecimalDegreesLongitude = pLongitude;

	//gpggaStruct->Velocity = CalculateDistance(gpggaStruct->DecimalDegreesLatitude, gpggaStruct->DecimalDegreesLongitude, gpggaStruct->PreviousDecimalDegreesLatitude, gpggaStruct->PreviousDecimalDegreesLongitude);

	return 0;
}

int GprmcStructHandler() {

}

int ResetArray(GPS_TEXT_ITEM gpsArray[30], int *pLoopCount) {
	for (int i = 0; i <= *pLoopCount; i++) {
		memset(gpsArray[i].item, 0, sizeof(gpsArray[i].item));
	}
	*pLoopCount = 0;
	return 0;
}

int ParseNmeaString(char sentence[NMEA_BYTE_BUFFER], GPS_TEXT_ITEM gpsArray[30], char tempHexnum[3], int *pLoopCount) {
	ResetArray(gpsArray, pLoopCount);
	char sentenceCopy[80];
	char *start, *end; // start and end value of data slice
	char *placeholder; // Holds value of &gpsArray[i]
	char *pSentence = sentence;
	int length; // length of data slice to put into array 
	
	*pLoopCount = 0;
	
	while (1) {
		// Start loop
		while (1) {
			if (*pSentence == ',' || *pSentence == '*' || *pSentence == '$') {
				pSentence++; // jump over , or $
				break;
			}
			pSentence++; // Keep jumping until you reach ,
		}

		strncpy(sentenceCopy, pSentence, sizeof(sentenceCopy));
		start = pSentence;

		// End loop
		while (1) {
			if (*pSentence == ',' || *pSentence == '\0' || *pSentence == '*') {
				break;
			}
			end = pSentence;
			pSentence++; // Keep jumping until you reach ,
		}
		end = pSentence;
		length = (int)(end - start); // get the end pointer which should be truncated
		sentenceCopy[length] = '\0'; // setting the truncation

		// putting parsed data into array
		memmove((gpsArray + *pLoopCount), sentenceCopy, sizeof(sentenceCopy));
		placeholder = gpsArray[*pLoopCount].item; // removes warning you get when putting gpsArray[i].item into printf
		//printf("Value: %d, %s\n", loopCount, placeholder);
		(*pLoopCount)++;
		if (strncmp(placeholder, tempHexnum, 2) == 0) {
			return 0;
		}
	}
	return 0;
}

int TypeNmeaString(char sentence[NMEA_BYTE_BUFFER], char *pTypeArray) {
	char *pSentence = sentence;
	pSentence++; // Jump over $
	
	for(uint_least8_t i = 0; i < 5; ++i) {
		*pTypeArray = *pSentence;
		pSentence++;
		pTypeArray++;
	}
	*pTypeArray = 0;
	return 0;
}

bool ValidateNmeaString(char sentence[NMEA_BYTE_BUFFER], char *pHexnum) {
	/* validCount is a green light system. Each check will + 1. If the total check value isnt 
	reached then its presumed a check failed*/
	uint_least8_t validCount = 0, decnum = 0, i = 0;
  	uint_least8_t length, rem;

  	char sentenceCopy[NMEA_BYTE_BUFFER], hexnum[3];
	char *pStart, *pEnd;
	char *pSentence = sentence;
	
	// Make a copy of sentence for * check
	strncpy(sentenceCopy, sentence, sizeof(sentenceCopy));

	//checking $ is the first value
	
	if (*pSentence == '$') {
		validCount++;
	}

	if (validCount == 1) {
		
		while (1) {
			if (*pSentence == '*') {
				validCount++;
				break;
			} else if(*pSentence == '\0') {
				break;
			}
			pSentence++;
		}
	}
	
	//check if checksum is correct
	
	// checksum string example: GPGLL,5300.97914,N,00259.98174,E,125926,A
	if (validCount == 2)
	{
    	pSentence = sentence;
		++pSentence; // jump over $
		pStart = pSentence;
		strncpy(sentenceCopy, pSentence, sizeof(sentenceCopy));
		
		while (1) {
			if (*pSentence == '*') {
				break;
			}
			pSentence += 1; // Keep jumping until you reach *
		}

		pEnd = pSentence; // get the end pointer which should be truncated
		length = (int)(pEnd - pStart); 
		sentenceCopy[length] = '\0'; // setting the truncation
		pEnd++; // Jump over the * so when comparing to the given checksum it doesnt include the * which isnt apart of the checksum value
		//XOR of all bytes
		for (int c = 0; c < strlen(sentenceCopy); c++) {
			decnum ^= sentenceCopy[c];
		}
		
		// convert decimal to hexadecimal
		for (int x = 0; x < 2; x++) {
			rem = decnum % 16;
			
			if(rem < 10) {
				rem += 48;
			}
			else {
				rem += 55;
			}
			// put rem into hexnum string array 1
			hexnum[i] = (char)rem;
			i++;
			decnum = decnum / 16;
		}
		hexnum[2] = 0;
		
		// Swap bits around. e.g. hexnum = 07, tempHexnum = 70
		*pHexnum = hexnum[1];
		pHexnum++;
		*pHexnum = hexnum[0];
		pHexnum++;
		*pHexnum = 0;
		pHexnum -= 2;
		for (uint_least8_t i = 0; i <= (strlen(pEnd)); ++i) {
			if(*pEnd != *pHexnum) {
				return 0;
			}
			pEnd++;
			pHexnum++;
		}
		validCount++;
	}
	// Returns
	
	if (validCount == 3) {
		return 1;
	} else {
		return 0;
	}
}

int DisplayLcd(float speed, int choice) {
	// speed is in meters per second
	// choice means the function returns different speeds, kmph = 0, mph = 1
	float kmph, mph;
	char charSpeed[6];
	int convertedSpeed;

	snprintf(charSpeed, sizeof(charSpeed), "%d", (int)speed);

	kmph = ((speed * 60) * 60) / 1000;
	mph = kmph * 0.621371;

	lcd.clear();
	lcd.print("Speed: ");
	lcd.setCursor(7, 0);
	lcd.print(charSpeed);
	lcd.setCursor((strlen(charSpeed) + 7), 0);
	lcd.print("m/s");

	return 0;
}

int ProcessNmeaString(char sentence[NMEA_BYTE_BUFFER], GPS_TEXT_ITEM gpsArray[30], GPGGA *gpggaStruct) {
	char tempHexnum[4], typeArray[6], latitude[14], longitude[14], previousLatitude[14], previousLongitude[14], velocityChar[2];
	int loopCount;
	float velocity = 0;
	TypeNmeaString(sentence, typeArray);

	if (ValidateNmeaString(sentence, tempHexnum) == 0) {
		//puts("Nmea string is not valid\n");
		//puts(sentence);
	} else {
		// check for type, call handlers, handlers parse and put into place, returns, 

		if (strncmp(typeArray, "GPGGA", 5) == 0) {
			GpggaStructHandler(sentence, gpsArray, tempHexnum, loopCount, gpggaStruct);
		} 
		if (strncmp(typeArray, "GPRMC", 5) == 0) {
			//puts(sentence);
		}
		if (strncmp(typeArray, "GPGSV", 5) == 0) {
			//puts(sentence);
		}
	}
	
	return 0;
}

int ReceiveNmeaStrings(char sentence[NMEA_BYTE_BUFFER], int messagePos, GPS_TEXT_ITEM gpsArray[30], GPGGA *gpggaStruct)
{
	while (Serial2.available() > 0) {
		
		byte nextByte = Serial2.read();

		if ((nextByte >= 32 && nextByte <= 126) || nextByte == '\n' || nextByte == '\r') {
			if (nextByte != '\n' && (messagePos < NMEA_BYTE_BUFFER - 1)) {
				sentence[messagePos] = nextByte;
				messagePos++;
			} else if (nextByte == '\n' || nextByte == '$') {
				sentence[messagePos] = '\0';
				//printf("Sentence: %s\n", sentence);
				ProcessNmeaString(sentence, gpsArray, gpggaStruct);

				memset(sentence, 0, NMEA_BYTE_BUFFER);
				messagePos = 0;
			} else {
				memset(sentence, 0, NMEA_BYTE_BUFFER);
				messagePos = 0;
			}
		} else {
			memset(sentence, 0, NMEA_BYTE_BUFFER);
			messagePos = 0;
		}
	}
	return 0;
}

// Haversine is an equation that lets you calculate the distance between two points on a sphere aka earth
double CalculateDistance(double lat1, double long1, double lat2, double long2)
{
	const uint_least16_t earthRadius = 6371; // kilometres
	const double radianConversion = (3.1415926536 / 180);
	lat1 *= radianConversion, long1 *= radianConversion, lat2 *= radianConversion, long2 *= radianConversion;

	//const double phi1 = lat1 * M_PI/180; // Theta and Lambda in radians
	//const double phi2 = lat2 * M_PI/180;
	const double deltaPhi = (lat2-lat1);
	const double deltaLambda = (long2-long1);
	const double value1 = sin(deltaPhi/2) * sin(deltaPhi/2) + cos(lat1) * cos(lat2) * sin(deltaLambda/2) * sin(deltaLambda/2); 
	const double value2 = 2 * atan2(sqrt(value1), sqrt(1-value1));
	const double result = earthRadius * value2;

	return result * 1000;
}

int ConvertDecimalDegrees(float Latitude, float Longitude, char NorthSouth[1], char EastWest[1], float *pLatitude, float *pLongitude) {
	// e.g. Latitude  04750.000
	// e.g. Longitude 11711.9258

	unsigned long tmpLat1;
	unsigned long tmpLong1;
	double tmpLat2;
	double tmpLong2;

	*pLatitude=Latitude/100;
	*pLongitude=Longitude/100;

	tmpLat1=(unsigned long)*pLatitude;
	tmpLat2=(double)tmpLat1;

	tmpLong1=(unsigned long)*pLongitude;
	tmpLong2=(double)tmpLong1;

	*pLatitude=*pLatitude-tmpLat2;
	*pLongitude=*pLongitude - tmpLong2;

	*pLatitude=*pLatitude*100/60;
	*pLongitude=*pLongitude*100/60;

	*pLatitude=*pLatitude+tmpLat1;
	*pLongitude=*pLongitude+tmpLong1;

	if (*NorthSouth == 'S') {
	*pLatitude = -*pLatitude;
	}
	if (*EastWest == 'W') {
	*pLongitude = -*pLongitude;
	}

	return 0;
}