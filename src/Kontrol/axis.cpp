/* (C)2019 Benjamin Schmid  
 *  
 *  axis.cpp
 */

#include "axis.h"

char* Axis::getName() {
  
  return this->name;
}

int16_t Axis::getPotiPin() {

  return this->potiPin;
}

int16_t Axis::getButtonUnprecise() {

  return this->buttonUnprecise;
}

int16_t Axis::getDeadband() {

  return this->deadband;
}

int16_t Axis::getPrecision() {

  return this->precision;
}

int16_t Axis::getMirror() {

  return this->mirror;
}

Axis::Axis(char name[6], int16_t potiPin, int16_t buttonUnprecise, int16_t deadband, int16_t precision, int16_t mirror) {

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
  Serial.println(this->getValue());
}

int16_t Axis::getValue() {

  //Because we map to a larger range than 16bit integer -> 1% deadband on the edges after constraining to 16bit integer
  int32_t reading = constrain(map(this->getReading(), 0, 1023, -33000, 33000), -32767, 32767);
  
  if(abs(reading) - this->getDeadband() < 0)
    reading = 0;

  //some axis are the wrong way
  reading = reading * this->getMirror();

  if (!(this->getUnprecise()))
    return (int16_t)(reading / this->getPrecision());
  else
    return (int16_t)reading;
}

int16_t Axis::getReading() {

  return analogRead(this->getPotiPin());
}

int16_t Axis::getUnprecise() {

  return digitalRead(this->getButtonUnprecise());
}
