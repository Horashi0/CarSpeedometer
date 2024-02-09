#include "Arduino_LED_Matrix.h"

const int SW_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;

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
   
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
}

void loop() {
  delay(100);
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

  Serial.print("X-axis: ");
  Serial.println(analogRead(X_pin));

  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));

  oldX = x;
  oldY = y;

  if(analogRead(X_pin) < 50 && x > 0)
  {
    x--;
  }
  if(analogRead(X_pin) > 1000 && x < 11)
  {
    x++;
  }
  if(analogRead(Y_pin) < 50 && y > 0)
  {
    y--;
  }
  if(analogRead(Y_pin) > 1000 && y < 7)
  {
    y++;
  }
  
  if(digitalRead(SW_pin))
  {
    for(int intX = 0; intX < 13; intX++)
    {
      for(int intY = 0; intY < 8; intY++)
      {
        frame[intY][intX] = 1;
      }

    }
  }


  frame[oldY][oldX] = 0;
  frame[y][x] = 1;

  matrix.renderBitmap(frame, 8, 12); 

}
