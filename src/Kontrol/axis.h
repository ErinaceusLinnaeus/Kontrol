/*  (C)2019 Benjamin Schmid
 *   
 *  axis.h
 *  Getting data of joystick axis
 */
 
#ifndef AXIS_H
#define AXIS_H

#include <arduino.h>

class Axis {

  private:
    char name[6];
    int16_t potiPin;
    int16_t buttonUnprecise;
    int16_t deadband;
    int16_t precision;
    int16_t precisionModifier;
    int16_t precisionTimer;
    int16_t mirror;
    
    //Getting Data
    char* getName();
    int16_t getPotiPin();
    int16_t getButtonUnprecise();
    int16_t getDeadband();
    int16_t getPrecision();
    int16_t getMirror();
    
  public:
    //Constructor
    Axis(char name[6], int16_t potiPin, int16_t buttonUnprecise, int16_t deadband, int16_t precision, int16_t mirror);

    //Debugging
    void check();

    //Getting Readings from hardware
    int16_t getValue();
    int16_t getReading();
    int16_t getUnprecise();
};

#endif
