/* (C)2019 Benjamin Schmid  
 *  
 *  joysticks.cpp
 */

#include "joysticks.h"
#include <arduino.h>

int buttonSASunprecise = 21;
int buttonRCSunprecise = 20;

//It's not that bad. 327.67 is 1%
//A variable deadband would be wonderful
//I'll think about that
int DeadbandPitch = 900;
int DeadbandYaw = 1700; //~5.5%
int DeadbandRoll = 650;

int DeadbandX = 1000;
int DeadbandY = 1000;
int DeadbandZ = 650;

int potiPitch = A0;
int potiYaw = A1;
int potiRoll = A2;

int potiX = A3;
int potiY = A4;
int potiZ = A5;

int precisionPitch = 3;
int precisionYaw = 3;
int precisionRoll = 10;

int precisionX = 10;
int precisionY = 10;
int precisionZ = 10;

void initializeJoystickPins() {
  
  pinMode(buttonSASunprecise, INPUT_PULLUP);
  pinMode(buttonRCSunprecise, INPUT_PULLUP);
  
  pinMode(potiPitch, INPUT);
  pinMode(potiYaw, INPUT);
  pinMode(potiRoll, INPUT);
  
  pinMode(potiX, INPUT);
  pinMode(potiY, INPUT);
  pinMode(potiZ, INPUT);
}

void checkJoysticks() {
  
  Serial.println("---");
  Serial.println("---");
    
  Serial.print("pitch : ");
  Serial.print(analogRead(potiPitch));
  Serial.print(" -> ");
  Serial.println(getSASpitch());
  Serial.print("yaw   : ");
  Serial.print(analogRead(potiYaw));
  Serial.print(" -> ");
  Serial.println(getSASyaw());
  Serial.print("roll  : ");
  Serial.print(analogRead(potiRoll));
  Serial.print(" -> ");
  Serial.println(getSASroll());

  Serial.print("x     : ");
  Serial.print(analogRead(potiX));
  Serial.print(" -> ");
  Serial.println(getRCSx());
  Serial.print("y     : ");
  Serial.print(analogRead(potiY));
  Serial.print(" -> ");
  Serial.println(getRCSy());
  Serial.print("z     : ");
  Serial.print(analogRead(potiZ));
  Serial.print(" -> ");
  Serial.println(getRCSz());
  delay(500);
}

//The range is supposed to be -32768, 32767 but it kept jumping to -32768
int getSASpitch() {
  
  int16_t SASpitch = map(analogRead(potiPitch), 0, 1023, -32700, 32700);
  
  if(abs(SASpitch) - DeadbandPitch < 0)
    SASpitch = 0;

  //pitch's the wrong way, of course
  SASpitch = SASpitch * -1;
    
  if (!digitalRead(buttonSASunprecise))
    return SASpitch / 3;
  else
    return SASpitch;
}

int getSASyaw() {
  
  int16_t SASyaw = map(analogRead(potiYaw), 0, 1023, -32700, 32700);
    
  if(abs(SASyaw) - DeadbandYaw < 0)
    SASyaw = 0;
  
  if (!digitalRead(buttonSASunprecise))
    return SASyaw / 3;
  else
    return SASyaw;
}

int getSASroll() {
    
  int16_t SASroll = map(analogRead(potiRoll), 0, 1023, -32700, 32700);
  
  if(abs(SASroll) - DeadbandRoll < 0)
    SASroll = 0;
  
  if (!digitalRead(buttonSASunprecise))
    return SASroll / 10;
  else
    return SASroll;
}

int getRCSx() {
  
  int16_t RCSx = map(analogRead(potiX), 0, 1023, -32700, 32700);
  
  if(abs(RCSx) - DeadbandX < 0)
    RCSx = 0;
  
  //x's the wrong way?
  RCSx = RCSx * -1;
    
  if (!digitalRead(buttonRCSunprecise))
    return RCSx / 10;
  else
    return RCSx;
  
}

int getRCSy() {
  
  int16_t RCSy = map(analogRead(potiY), 0, 1023, -32700, 32700);;
  
  if(abs(RCSy) - DeadbandY < 0)
    RCSy = 0;
  
  if (!digitalRead(buttonRCSunprecise))
    return RCSy / 10;
  else
    return RCSy;
  
}

int getRCSz() {
  
  int16_t RCSz = map(analogRead(potiZ), 0, 1023, -32700, 32700);
  
  if(abs(RCSz) - DeadbandZ < 0)
    RCSz = 0;

  //z's the wrong way, forward is negative?
  RCSz = RCSz * -1;
    
  if (!digitalRead(buttonRCSunprecise))
    return RCSz / 10;
  else
    return RCSz;
  
}

 
