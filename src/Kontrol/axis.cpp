/* (C)2019 Benjamin Schmid  
 *  
 *  axis.cpp
 */

#include "axis.h"

char* Axis::getName() {
  
  return this->name;
}

int Axis::getPotiPin() {

  return this->potiPin;
}

int Axis::getButtonUnprecise() {

  return this->buttonUnprecise;
}

int Axis::getDeadband() {

  return this->deadband;
}

int Axis::getPrecision() {

  return this->precision;
}

int Axis::getMirror() {

  return this->mirror;
}

Axis::Axis(char name[6], int potiPin, int buttonUnprecise, int deadband, int precision, int mirror) {

  pinMode(buttonUnprecise, INPUT_PULLUP);
  pinMode(potiPin, INPUT);
  
  strcpy(this->name, name);
  this->potiPin = potiPin;
  this->buttonUnprecise = buttonUnprecise;
  this->deadband = deadband;
  this->precision = precision;
  this->mirror = mirror;
}

void Axis::check() {

  Serial.print(this->getName());
  Serial.print(" : ");
  Serial.print(this->getReading());
  Serial.print(" -> ");
  Serial.print(this->getValue());
}

int Axis::getValue() {

  int reading = map(this->getReading(), 0, 1023, -32768, 32767);
  //to be sure to stay in integers range
  reading = constrain(reading, -32768, 32767);
  
  if(abs(reading) - this->getDeadband() < 0)
    reading = 0;

  //some axis are the wrong way
  reading = reading * getMirror();
    
  if (!this->getUnprecise())
    return reading / this->getPrecision();
  else
    return reading;
}

int Axis::getReading() {

  return analogRead(this->getPotiPin());
}

int Axis::getUnprecise() {

  return digitalRead(this->getUnprecise());
}
