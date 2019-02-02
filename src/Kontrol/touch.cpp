/* (C)2019 Benjamin Schmid  
 *  
 *  touch.cpp
 */

#include "touch.h"

void TouchPanel::check() {

  Serial.print("x : ");
  Serial.print(this->getPreciseX());
  Serial.print(" -> ");
  Serial.println(this->getStoreyX());
  Serial.print("y     : ");
  Serial.print(this->getPreciseY());
  Serial.print(" -> ");
  Serial.println(this->getStoreyY());
  Serial.print("z : ");
  Serial.println(this->getTouchZ());
}

int TouchPanel::getStoreyX() {

  //Monitor is 1366x768
  p = ts.getPoint();
  int x = map(p.x, 150, 830, 0, 800);

  //Getting the ccoordinates by the 100's
  x = x / 100 + 1;
  
  //Idle
  if (getTouchZ())
    return x;
  else
    return 0;
}

int TouchPanel::getStoreyY() {
  
  //Monitor is 1366x768
  p = ts.getPoint();
  int y = map(p.y, 150, 935, 0, 1000);

  //Getting the ccoordinates by the 100's
  y = y / 100 + 1;
  
  //Idle
  if (getTouchZ())
    return y;
  else
    return 0;
}

int TouchPanel::getTouchZ() {

  //Monitor is 1366x768
  p = ts.getPoint();
  //Getting the pressure
  return (p.z > 0);
}

int TouchPanel::getPreciseX() {
  
  p = ts.getPoint();
  return map(p.x, 150, 830, 0, 800);
}

int TouchPanel::getPreciseY() {
  
  p = ts.getPoint();
  return map(p.y, 150, 935, 0, 1000);
}

int TouchPanel::getPreciseZ() {

  p = ts.getPoint();
  //Getting the pressure
  return p.z;
}
