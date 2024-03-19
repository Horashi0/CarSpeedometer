#pragma once

//definitions of lengths
#define GPGGA_ID_LENGTH 5 // All NMEA Id's are 5 characters long
#define GPGGA_UTC_LENGTH 10 // UTC timestamps are all 10 characters long
#define GPGGA_NORTH_SOUTH_LENGTH 1 // NorthSouth strings are all 1 character long
#define GPGGA_EAST_WEST_LENGTH 1 // EastWest strings are all 1 character long
#define GPGGA_FIXED_FIELD1_LENGTH 1 // Fixed Field, meter
#define GPGGA_FIXED_FIELD2_LENGTH 1 // Fixed Field, meter
#define GPGGA_CHECKSUM_LENGTH 2 // Checkusum is a 2 character long hexadecimal
#define GPGGA_DGPS_AGE_LENGTH 4 // DgpsAge is in seconds so 4 is a sufficient length
#define GPGGA_DGPS_STATION_ID_LENGTH 4 // Range 0000 to 4095

typedef struct 
{
	char Id[GPGGA_ID_LENGTH+1]; // ID for NMEA string. e.g. GPGGA
	char UtcTime[GPGGA_UTC_LENGTH + 1]; // UTC timestamp for NMEA string - Time in format ‘hhmmss.sss’ e.g. 135716.174
	float Latitude; // Latitude for NMEA string - Latitude in format ‘ddmm.mmmm’ (degree and minutes)
	float DecimalDegreesLatitude; // Converted format of Latitude
	float PreviousDecimalDegreesLatitude; // Converted format of previous longitude value
	char NorthSouth[GPGGA_NORTH_SOUTH_LENGTH + 1]; // North/South character for NMEA string - 'N'= North 'S'= South
	float Longitude; // Longitude for NMEA string - Longitude in format ‘dddmm.mmmm’ (degree and minutes)
	float DecimalDegreesLongitude; // Converted format of Longitude
	float PreviousDecimalDegreesLongitude; // Converted format of previous longitude value
	char EastWest[GPGGA_EAST_WEST_LENGTH + 1]; // East/West character for NMEA string - ‘E’=East ‘W’ = West
	int FixStatus; // Fix Status for NMEA string - ‘0’=Invalid	 ‘1’ = GPS fix	 ‘2’ = DGPS fix
	int Nos; // Number of satellites for NMEA string - Number of satellites being used (0~12)
	float Hdop; // Horizontal Dilution Of Precision
	float Altitude; // Altitude in meters according to WGS84 ellipsoid
	char FixedField1[GPGGA_FIXED_FIELD1_LENGTH + 1]; // Fixed field, meter
	float GeoID; // Height of GeoID (mean sea level) above WGS84 ellipsoid, meter
	char FixedField2[GPGGA_FIXED_FIELD2_LENGTH + 1]; // Fixed field, meter
	char DgpsAge[GPGGA_DGPS_AGE_LENGTH + 1]; // Age of DGPS data in seconds, empty if DGPS is not used
	char DgpsStationID[GPGGA_DGPS_STATION_ID_LENGTH + 1]; // DGPS station ID, empty if DGPS is not used
	char CheckSum[GPGGA_CHECKSUM_LENGTH + 1]; // Hexadecimal checksum
}GPGGA; 