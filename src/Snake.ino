#include "Arduino_LED_Matrix.h"

const int SW_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;

ArduinoLEDMatrix matrix;

int x = 0;
int y = 0;
int appleStatus = 0;

int score = 1;
int length = 1;
int randY, randX = 0;
int ArrayIndex = 0;
int oldX, oldY = 0;


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

int PositioningArray[50];


void setup() {
  Serial.begin(115200);
  matrix.begin();

  PositioningArray[ArrayIndex] = 1;
  PositioningArray[ArrayIndex + 1] = 0;
  PositioningArray[ArrayIndex + 2] = 0;
  ArrayIndex += 3;

   
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

  SnakeLength();
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

  int lengthUpdate = 1;

  // Only updates when oldY and y etc are different as this function is called thousands of times a second

  // Program works by just iterating the snake along, then if length goes over score it fixes it

  if(oldY != y || oldX != x)
  {
    length++;
    PositioningArray[ArrayIndex] = length;
    PositioningArray[ArrayIndex + 1] = y;
    PositioningArray[ArrayIndex + 2] = x;

    ArrayIndex += 3;
  }

  if(length > score)
  {
    // As length is appended to array before the x and y coords this means you can find what length the snake was when the coords were appended

    // This means when length goes over score you can find where scores value is then set the values after to 0

    // But this program only allows snake to go over length by one
    for(int i = 0; i < 50; i++)
    {
      if(PositioningArray[i] == score) 
      {
        frame[PositioningArray[i + 1]][PositioningArray[i + 2]] = 0;
        length--;
        break;
      }
    }

    // Need to resort array now that its out of order/messed up
    for(int i = 3; i < 50; i++)
    {
      PositioningArray[i - 3] = PositioningArray[i];
    }
    ArrayIndex = 3;

    for(int i = 0; i < 50; i += 3)
    {
      Serial.print("Array: ");
      PositioningArray[i] = lengthUpdate;
      Serial.println(PositioningArray[i]);
      lengthUpdate++;
    }

  }

  frame[y][x] = 1;
  
  matrix.renderBitmap(frame, 8, 12); 
}