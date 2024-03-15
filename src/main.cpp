#include <Arduino.h>
#include <SoftwareSerial.h>
#include <stdio.h>

const byte rxPin = 8;
const byte txPin = 9;

#define NMEA_BYTE_BUFFER 128

SoftwareSerial GpsSerial(rxPin, txPin);
static char Sentence[NMEA_BYTE_BUFFER];
static int messagePos = 0;


void setup() {
  Serial.begin(9600);

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  GpsSerial.begin(9600);
}

void loop() {
  while(GpsSerial.available() > 0) {
    byte nextByte = GpsSerial.read();
    //printf("%c", nextByte);

    if ((nextByte >= 32 && nextByte <= 126) || nextByte == '\n' || nextByte == '\r') {
      if (nextByte != '\n' && (messagePos < NMEA_BYTE_BUFFER - 1)) {
        Sentence[messagePos] = nextByte;
        messagePos++;
      } else if (nextByte == '\n' || nextByte == '$') {
        Sentence[messagePos] = '\0';
        memset(Sentence, 0, sizeof(Sentence));
        messagePos = 0;
      } else {
        memset(Sentence, 0, sizeof(Sentence));
        messagePos = 0;
      }
    } else {
      memset(Sentence, 0, sizeof(Sentence));
      messagePos = 0;
    }
  }
}

