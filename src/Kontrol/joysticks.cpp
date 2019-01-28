

#include "joysticks.h"
#include <arduino.h>

int buttonSASunprecise = 21;
int buttonRCSunprecise = 20;

//It's not that bad. 327.67 is 1%
//A variable deadband would be wonderful
//I'll think about that
int joysticksDeadbandPitch = 900;
int joysticksDeadbandYaw = 1700; //~5.5%
int joysticksDeadbandRoll = 650;

int joysticksDeadbandX = 1000;
int joysticksDeadbandY = 1000;
int joysticksDeadbandZ = 650;

int potiSASpitch = A0;
int potiSASyaw = A1;
int potiSASroll = A2;

int potiRCSx = A3;
int potiRCSy = A4;
int potiRCSz = A5;

void initializePins() {
  
  pinMode(buttonSASunprecise, INPUT_PULLUP);
  pinMode(buttonRCSunprecise, INPUT_PULLUP);
  
  pinMode(potiSASpitch, INPUT);
  pinMode(potiSASyaw, INPUT);
  pinMode(potiSASroll, INPUT);
  
  pinMode(potiRCSx, INPUT);
  pinMode(potiRCSy, INPUT);
  pinMode(potiRCSz, INPUT);
}

//The range is supposed to be -32768, 32767 but it kept jumping to -32768
int getSASpitch() {
  
  int16_t SASpitch = map(analogRead(potiSASpitch), 0, 1023, -32700, 32700);
  
  if(abs(SASpitch) - joysticksDeadbandPitch < 0)
    SASpitch = 0;

  //pitch's the wrong way, of course
  SASpitch = SASpitch * -1;
    
  if (!digitalRead(buttonSASunprecise))
    return SASpitch / 10;
  else
    return SASpitch;
}

int getSASyaw() {
  
  int16_t SASyaw = map(analogRead(potiSASyaw), 0, 1023, -32700, 32700);
    
  if(abs(SASyaw) - joysticksDeadbandYaw < 0)
    SASyaw = 0;
    
  if (!digitalRead(buttonSASunprecise))
    return SASyaw / 10;
  else
    return SASyaw;
}

int getSASroll() {
    
  int16_t SASroll = map(analogRead(potiSASroll), 0, 1023, -32700, 32700);
  
  if(abs(SASroll) - joysticksDeadbandRoll < 0)
    SASroll = 0;
    
  if (!digitalRead(buttonSASunprecise))
    return SASroll / 10;
  else
    return SASroll;
}

int getRCSx() {
  
  int16_t RCSx = map(analogRead(potiRCSx), 0, 1023, -32700, 32700);
  
  if(abs(RCSx) - joysticksDeadbandX < 0)
    RCSx = 0;

  //x's the wrong way?
  RCSx = RCSx * -1;
    
  if (!digitalRead(buttonRCSunprecise))
    return RCSx / 10;
  else
    return RCSx;
  
}

int getRCSy() {
  
  int16_t RCSy = map(analogRead(potiRCSy), 0, 1023, -32700, 32700);;
  
  if(abs(RCSy) - joysticksDeadbandY < 0)
    RCSy = 0;
    
  if (!digitalRead(buttonRCSunprecise))
    return RCSy / 10;
  else
    return RCSy;
  
}

int getRCSz() {
  
  int16_t RCSz = map(analogRead(potiRCSz), 0, 1023, -32700, 32700);
  
  if(abs(RCSz) - joysticksDeadbandZ < 0)
    RCSz = 0;

  //z's the wrong way, forward is negative?
  RCSz = RCSz * -1;
    
  if (!digitalRead(buttonRCSunprecise))
    return RCSz / 10;
  else
    return RCSz;
  
}

 
