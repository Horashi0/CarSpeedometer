#include "Arduino_LED_Matrix.h"

const int SW_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;

ArduinoLEDMatrix matrix;

int x = 0;
int y = 0;
int oldX = 0;
int oldY = 0;
int appleStatus = 0;
int randY = 0;
int randX = 0;
int score = 1;



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
  delay(150);

  Apple();

  /*
  Debug print out

  Serial.print("X-axis: ");
  Serial.println(analogRead(X_pin));

  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  */

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

  frame[oldY][oldX] = 0;
  frame[y][x] = 1;

  matrix.renderBitmap(frame, 8, 12); 
}

void Apple()
{
  if(appleStatus == 0)
  {
    randY = random(0,7);
    randX = random(0,11);

    frame[randY][randX] = 1;
    appleStatus = 1;
  }

  if(frame[randY][randX] == 0)
  {
    score++;
    appleStatus = 0;
  }
}

void SnakeLength()
{
  
}