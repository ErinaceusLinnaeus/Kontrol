/* (C)2019 Benjamin Schmid  
 *  
 *  touch.cpp
 */

#include "touch.h"
#include <arduino.h>
#include <TouchScreen.h>

//Pins connected to the touchscreen
int YP = A10;
int XM = A11;
int YM = 14;
int XP = 15;
//global variables to get coordinates
int x;
int y;
TSPoint p;

// For better pressure precision: I messured 540 Ohm between XP and XM
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 540);

void checkTouch() {

  Serial.print("x     : ");
  Serial.println(getStoreyX());
  Serial.print("y     : ");
  Serial.println(getStoreyY());
  Serial.print("z     : ");
  Serial.println(p.z);
}

int getStoreyX() {

  //Monitor is 1366x768
  p = ts.getPoint();
  //Values while idle: x:-176, y:1112, z:0
  x = map(p.x, 150, 830, 0, 800);

  //Getting the ccoordinates by the 100's
  x = x / 100 + 1;
  
  //Idle
  if (getTouchZ())
    return x;
  else
    return 0;
}

int getStoreyY() {
  
  //Monitor is 1366x768
  p = ts.getPoint();
  //Values while idle: x:-176, y:1112, z:0
  y = map(p.y, 150, 935, 0, 1100);

  //Getting the ccoordinates by the 100's
  y = y / 100 + 1;
  
  //Idle
  if (getTouchZ())
    return y;
  else
    return 0;
}

int getTouchZ() {

  //Monitor is 1366x768
  p = ts.getPoint();
  //Getting the pressure
  return (p.z > 0);
}

int getPreciseX() {
  
  p = ts.getPoint();
  return map(p.x, 150, 830, 0, 800);
}

int getPreciseY() {
  
  p = ts.getPoint();
  return y = map(p.y, 150, 935, 0, 1100);
}
