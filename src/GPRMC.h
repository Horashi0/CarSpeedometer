#pragma once

// Length defines
#define GPRMC_ID_LENGTH 5 // All NMEA Id's are 5 characters long
#define GPRMC_UTC_LENGTH 10 // UTC timestamps are all 10 characters long
#define GPRMC_DATA_VALID_LENGTH 1 // Data validity are all one character long
#define GPRMC_LATITUDE_LENGTH 15 // Latitude strings are all 12 characters long
#define GPRMC_NORTH_SOUTH_LENGTH 1 // NorthSouth strings are all 1 character long
#define GPRMC_LONGITUDE_LENGTH 15 // Longitude strings are all 12 characters long
#define GPRMC_EAST_WEST_LENGTH 1 // EastWest strings are all 1 character long
#define GPRMC_DATE_LENGTH 4 // Date is ddmmyy so 4 characters is sufficient
#define GPRMC_MAGNETIC_VARIATION_LENGTH 4 // Magnetic variation in degrees so 4 characters is sufficient
#define GPRMC_MAGNETIC_EAST_WEST_LENGTH 1 // MagneticEastWest strings are all 1 character long
#define GPRMC_POSITIONING_LENGTH 1// Positioning length strings are all 1 character long
#define GPRMC_CHECKSUM_LENGTH 2 // Checksum is a 2 character long hexadecimal number
typedef struct {
	char Id[GPRMC_ID_LENGTH + 1]; // ID for NMEA string. e.g. GPRMC
	char UtcTime[GPRMC_UTC_LENGTH + 1]; // UTC timestamp for NMEA string - Time in format ‘hhmmss.sss’ e.g. 135716.174
	char DataValid[GPRMC_DATA_VALID_LENGTH + 1]; // Data valid character for NMEA string - 'V'=Invalid 'A'=Valid
	float Latitude; // Latitude for NMEA string - Latitude in format ‘ddmm.mmmm’ (degree and minutes)
	char NorthSouth[GPRMC_NORTH_SOUTH_LENGTH + 1]; // North/South character for NMEA string - 'N'= North 'S'= South
	float Longitude; // Longitude for NMEA string - Longitude in format ‘dddmm.mmmm’ (degree and minutes)
	char EastWest[GPRMC_EAST_WEST_LENGTH + 1]; // East/West character for NMEA string - ‘E’=East ‘W’ = West
	float Speed; // Speed over ground in knots
	float Cog; // Course over ground in degree
	char Date[GPRMC_DATE_LENGTH + 1]; // Date in format 'ddmmyy'
	char MagneticVariation[GPRMC_MAGNETIC_VARIATION_LENGTH + 1]; // Magnetic variation in degree, not being output
	char MagneticEastWest[GPRMC_MAGNETIC_EAST_WEST_LENGTH + 1]; // Magnetic variation E/W indicator, not being output
	char PositioningMode[GPRMC_POSITIONING_LENGTH + 1]; // N’=No fix ‘A’ = Autonomous GPS fix ‘D’ = Differential GPS fix
	char Checksum[GPRMC_CHECKSUM_LENGTH + 1]; // 2 character long Hexadecimal Checksum

}GPRMC;