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

  //Checking if we're inside the deadband
  if(abs(reading) - this->getDeadband() < 0)
    reading = 0;

  //some axis are the wrong way
  reading = reading * this->getMirror();

  //If the precision button is pressed...
    //...just return the reading modified by the factor of precision
  //Else calculate the modifier:
    //500 (ms) => 1
    //250 (ms) => 1/2
    // If the modifier redcues the reading more than the base-precision...
      //...use the base-precision
    //Else...
      //...use thhe modifier
  if (!(this->getUnprecise())) {
    return (int16_t)(reading / this->getPrecision());
  }
  else {
    float tmp = ((millis() - precisionTimer) / 500);

    if ((reading * tmp) < (reading / this->getPrecision()))
      return (int16_t)(reading / this->getPrecision());
    else
      return (int16_t)(reading * tmp);
  }
}

int16_t Axis::getReading() {

  return analogRead(this->getPotiPin());
}

int16_t Axis::getUnprecise() {

  int16_t tmp = digitalRead(this->getButtonUnprecise());

  //If the precision button is pressed set the timer to calculate the time the button will be released
  if (!tmp) {
    this->precisionTimer = millis();
  }
  
  return tmp;
}
