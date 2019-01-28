

#include "touch.h"
#include <arduino.h>

int touchX = A6;
int touchY = A7;

void initializeTouchPins() {
  
  pinMode(touchX, INPUT);
  pinMode(touchY, INPUT);
}

void checkTouch() {
  
  Serial.println("---");
  Serial.println("---");
    
  Serial.print("x : ");
  Serial.print(analogRead(touchX));
  Serial.print(" -> ");
  Serial.println(getTouchX());
  Serial.print("y   : ");
  Serial.print(analogRead(touchY));
  Serial.print(" -> ");
  Serial.println(getTouchY());
  delay(500);
}

int getTouchX() {
  return map(analogRead(touchX), 0, 1023, 0, 1366);
}

int getTouchY() {
  return map(analogRead(touchY), 0, 1023, 0, 768);
}
