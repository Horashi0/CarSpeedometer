#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

int x = 0;
int y = 0;
int oldX = 0;
int oldY = 0;

byte frame[8][12] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void setup() {
  Serial.begin(115200);
  matrix.begin();
 
}

void loop() {
  /*
  byte frame[8][12] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };
  matrix.renderBitmap(frame, 8, 12);
  */
  if(Serial.available() > 0)
  {    
    char byte = Serial.read();
    Serial.println(byte);

    oldX = x;
    oldY = y;

    if(byte == 'L' && y > 0)
    {
      y--;
    }
    if(byte == 'R' && y < 11)
    {
      y++;
    }
    if(byte == 'U' && x > 0)
    {
      x--;
    }
    if(byte == 'D' && x < 7)
    {
      x++;
    }

    if(byte == 'F')
    {
      for(int intY = 0; intY < 13; intY++)
      {
        for(int intX = 0; intX < 8; intX++)
        {
          frame[intX][intY] = 1;
        }

      }
    }

    Serial.println(y);
    Serial.println(x);

    frame[oldX][oldY] = 0;
    frame[x][y] = 1;

    matrix.renderBitmap(frame, 8, 12);
  }
  

}
