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
    int potiPin;
    int buttonUnprecise;
    int deadband;
    int precision;
    int mirror;
    
    //Getting Data
    char* getName();
    int getPotiPin();
    int getButtonUnprecise();
    int getDeadband();
    int getPrecision();
    int getMirror();
    
  public:
    //Constructor
    Axis(char name[6], int potiPin, int buttonUnprecise, int deadband, int precision, int mirror);

    //Debugging
    void check();

    //Getting Readings from hardware
    int getValue();
    int getReading();
    int getUnprecise();
};

#endif
