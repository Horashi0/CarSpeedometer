#include <Arduino.h>
#include <SoftwareSerial.h>
#include <stdio.h>
#include <math.h>

#include "main.hpp"
#include "GPGGA.h"
#include "GPRMC.h"

#define NMEA_BYTE_BUFFER 128

const byte rxPin = 8;
const byte txPin = 9;
SoftwareSerial GpsSerial(rxPin, txPin);

char Sentence[NMEA_BYTE_BUFFER];
char typeArray[5];
int MessagePos = 0;

GPGGA *GpggaStruct;
GPRMC *GprmcStruct;

void setup() {
  Serial.begin(9600);

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  GpsSerial.begin(9600);
}

void loop() {
	ReceiveNmeaStrings();
}

void GpggaStructHandler() {

}

void GprmcStructHandler() {

}


char *TypeNmeaString() {
	char *pSentence = Sentence;
	pSentence++; // Jump over $
	
	for(uint_least8_t i = 0; i < 5; ++i) {
		typeArray[i] = *pSentence;
		pSentence++;
	}
	typeArray[5] = 0;
	
	return typeArray;
}

bool ValidateNmeaString() {
	/* validCount is a green light system. Each check will + 1. If the total check value isnt 
	reached then its presumed a check failed*/
	uint_least8_t validCount = 0, decnum = 0, i = 0;
  	uint_least8_t length, rem;

  	char sentenceCopy[80], hexnum[3], tempHexnum[3];
	char *pStart, *pEnd;
	char *pSentence = Sentence;
	
	// Make a copy of sentence for * check
	strncpy(sentenceCopy, Sentence, sizeof(sentenceCopy));

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
    	pSentence = Sentence;
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
			
			if(rem < 10)
			{
				rem += 48;
			}
			else
			{
				rem += 55;
			}
			// put rem into hexnum string array 1
			hexnum[i] = (char)rem;
			i++;
			decnum = decnum / 16;
		}
		hexnum[2] = 0;
		
		// Swap bits around. e.g. hexnum = 07, tempHexnum = 70
		tempHexnum[0] = hexnum[1];
		tempHexnum[1] = hexnum[0];
		tempHexnum[2] = 0;
		//printf("String: %s\n", Sentence);
		//printf("Hexnum: %s\n", tempHexnum);
		//printf("End: %s\n", end);
		for (uint_least8_t i = 0; i <= (strlen(pEnd)); ++i) {
			if(*pEnd != tempHexnum[i])
			{
				return 0;
			}
			pEnd++;
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

void ProcessNmeaString() {
	char *pType;
	if (ValidateNmeaString() == 0) {
		puts("Nmea string is not valid\n");
	} else {
		pType = TypeNmeaString();
		// check for type, call handlers, handlers parse and put into place, returns, 

		if (strncmp(pType, "GPGGA", 5) == 0) {
			puts(Sentence);
		}
		if (strncmp(pType, "GPRMC", 5) == 0) {
			puts(Sentence);
		}
	}
}

void ReceiveNmeaStrings()
{
	while (GpsSerial.available() > 0) {
		
		byte nextByte = GpsSerial.read();

		if ((nextByte >= 32 && nextByte <= 126) || nextByte == '\n' || nextByte == '\r') {
			if (nextByte != '\n' && (MessagePos < NMEA_BYTE_BUFFER - 1)) {
				Sentence[MessagePos] = nextByte;
				MessagePos++;
			} else if (nextByte == '\n' || nextByte == '$') {
				Sentence[MessagePos] = '\0';
				ProcessNmeaString();

				memset(Sentence, 0, sizeof(Sentence));
				MessagePos = 0;
			} else {
				memset(Sentence, 0, sizeof(Sentence));
				MessagePos = 0;
			}
		} else {
			memset(Sentence, 0, sizeof(Sentence));
			MessagePos = 0;
		}
	}
}
;
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