/* (C)2019 Benjamin Schmid  
 *  
 *  communication.cpp
 */

#include "communication.h"

//KerbalSimPit
#include <KerbalSimpit.h>
#include <KerbalSimpitMessageTypes.h>
#include <PayloadStructs.h>

// Declare a KerbalSimpit object that will
// communicate using the "Serial" device.
KerbalSimpit mySimpit(Serial);

int AbortFlag = 0;
const long AbortDelay = 500;
long previousAbort = 0;
const long CommDelay = 200;
long previousComm = 0;

void initializeSimpit() {
      
  // This loop continually attempts to handshake with the plugin.
  // It will keep retrying until it gets a successful handshake.
  while (!mySimpit.init());

  //needed to send throttle
  mySimpit.registerChannel(THROTTLE_MESSAGE);
  //needed to send attitude
  mySimpit.registerChannel(ROTATION_MESSAGE);
  //needed to send translation
  mySimpit.registerChannel(TRANSLATION_MESSAGE);
  //needed to send translation
  mySimpit.registerChannel(SAS_MODE_MESSAGE);
}

void updateSimpit() {
      
  mySimpit.update();
}

int checkAbortFlag() {
  if (AbortFlag && ((millis() - previousAbort) > AbortDelay)) {
    AbortFlag = 0;
    return 1;
  }
  else {
    previousAbort = millis();
    AbortFlag = 1;
    return 0;
  }
}

void unsetAbortFlag() {
  AbortFlag = 0;
}

void sendCommand(uint32_t command, uint32_t value) {

  if ((millis() - previousComm) > CommDelay) {

    previousComm = millis();
    
    if (command == NIX) {
      NULL;
    }
    else if (command == acgStage) {
      unsetAbortFlag();
      mySimpit.activateAction(STAGE_ACTION);
    }
    else if (command == acgAbort) {
      if (checkAbortFlag() || value == 0) {
        mySimpit.activateAction(ABORT_ACTION);
      }
      else {
        NULL;
      }
    }
    else if (command == acgLight) {
      unsetAbortFlag();
      if (value == 0)
        mySimpit.deactivateAction(LIGHT_ACTION);
      else if (value == 1)
        mySimpit.toggleAction(LIGHT_ACTION);
      else if (value == 2)
        mySimpit.activateAction(LIGHT_ACTION);
    }
    else if (command == acgGear) {
      unsetAbortFlag();
      if (value == 0)
        mySimpit.deactivateAction(GEAR_ACTION);
      else if (value == 1)
        mySimpit.toggleAction(GEAR_ACTION);
      else if (value == 2)
        mySimpit.activateAction(GEAR_ACTION);
    }
    else if (command == acgBrakes) {
      unsetAbortFlag();
      if (value == 0)
        mySimpit.deactivateAction(BRAKES_ACTION);
      else if (value == 1)
        mySimpit.toggleAction(BRAKES_ACTION);
      else if (value == 2)
        mySimpit.activateAction(BRAKES_ACTION);
    }
    else if (command == acgRCS) {
      unsetAbortFlag();
      if (value == 0)
        mySimpit.deactivateAction(RCS_ACTION);
      else if (value == 1)
        mySimpit.toggleAction(RCS_ACTION);
      else if (value == 2)
        mySimpit.activateAction(RCS_ACTION);
    }
    else if (command == acgSAS) {
      unsetAbortFlag();
      if (value == 0)
        mySimpit.deactivateAction(SAS_ACTION);
      else if (value == 1)
        mySimpit.toggleAction(SAS_ACTION);
      else if (value == 2)
        mySimpit.activateAction(SAS_ACTION);
    }
    else if (command == acg1 || command == acg2 || command == acg3 || command == acg4 || command == acg5 ||
             command == acg6 || command == acg7 || command == acg8 || command == acg9 || command == acg10){
      unsetAbortFlag();
      if (value == 0)
        mySimpit.deactivateCAG(command);
      else if (value == 1)
        mySimpit.toggleCAG(command);
      else if (value == 2)
        mySimpit.activateCAG(command);
    }
    else if (command == sasStability) {
      unsetAbortFlag();
      mySimpit.activateAction(SAS_ACTION);
      delay(50);
      AutopilotMode mySASMode = AP_STABILITYASSIST;
      mySimpit.send(28, (unsigned char*) &mySASMode, 1);
//      mySimpit.setSASMode(AP_STABILITYASSIST);
    }
    else if (command == sasManeuver) {
      unsetAbortFlag();
      mySimpit.activateAction(SAS_ACTION);
      delay(50);
      AutopilotMode mySASMode = AP_MANEUVER;
      mySimpit.send(28, (unsigned char*) &mySASMode, 1);
//      mySimpit.setSASMode(AP_MANEUVER);
    }
    else if (command == sasPrograde) {
      unsetAbortFlag();
      mySimpit.activateAction(SAS_ACTION);
      delay(50);
      AutopilotMode mySASMode = AP_PROGRADE;
      mySimpit.send(28, (unsigned char*) &mySASMode, 1);
//      mySimpit.setSASMode(AP_PROGRADE);
    }
    else if (command == sasRetrograde) {
      unsetAbortFlag();
      mySimpit.activateAction(SAS_ACTION);
      delay(50);
      AutopilotMode mySASMode = AP_RETROGRADE;
      mySimpit.send(28, (unsigned char*) &mySASMode, 1);
//      mySimpit.setSASMode(AP_RETROGRADE);
    }
    else if (command == sasNormal) {
      unsetAbortFlag();
      mySimpit.activateAction(SAS_ACTION);
      delay(50);
      AutopilotMode mySASMode = AP_NORMAL;
      mySimpit.send(28, (unsigned char*) &mySASMode, 1);
//      mySimpit.setSASMode(AP_NORMAL);
    }
    else if (command == sasAntinormal) {
      unsetAbortFlag();
      mySimpit.activateAction(SAS_ACTION);
      delay(50);
      AutopilotMode mySASMode = AP_ANTINORMAL;
      mySimpit.send(28, (unsigned char*) &mySASMode, 1);
//      mySimpit.setSASMode(AP_ANTINORMAL);
    }
    else if (command == sasRadialin) {
      unsetAbortFlag();
      mySimpit.activateAction(SAS_ACTION);
      delay(50);
      AutopilotMode mySASMode = AP_RADIALIN;
      mySimpit.send(28, (unsigned char*) &mySASMode, 1);
//      mySimpit.setSASMode(AP_RADIALIN);
    }
    else if (command == sasRadialout) {
      unsetAbortFlag();
      mySimpit.activateAction(SAS_ACTION);
      delay(50);
      AutopilotMode mySASMode = AP_RADIALOUT;
      mySimpit.send(28, (unsigned char*) &mySASMode, 1);
//      mySimpit.setSASMode(AP_RADIALOUT);
    }
    else if (command == sasTarget) {
      unsetAbortFlag();
      mySimpit.activateAction(SAS_ACTION);
      delay(50);
      AutopilotMode mySASMode = AP_TARGET;
      mySimpit.send(28, (unsigned char*) &mySASMode, 1);
//      mySimpit.setSASMode(AP_TARGET);
    }
    else if (command == sasAntitarget) {
      unsetAbortFlag();
      mySimpit.activateAction(SAS_ACTION);
      delay(50);
      AutopilotMode mySASMode = AP_ANTITARGET;
      mySimpit.send(28, (unsigned char*) &mySASMode, 1);
//      mySimpit.setSASMode(AP_ANTITARGET);
    }
    //Temporary bugfix. Plugin seems to listen to the wrong "channel".
  //  AutopilotMode mySASMode;
  // mySimpit.send(28, (unsigned char*) &mySASMode, 1);
  // mySimpit.send(SAS_MODE_MESSAGE, (unsigned char*) &mySASMode, 1);
    else if (command == setThrottle) {
      unsetAbortFlag();
      sendThrottle(value);
    }
    else if (command == keyMap) {
      unsetAbortFlag();
      Keyboard.begin();
      Keyboard.print('m'); 
      Keyboard.end();
    }
    else if (command == keyWarpInc) {
      unsetAbortFlag();
      Keyboard.begin();
      Keyboard.print('.'); 
      Keyboard.end();
    }
    else if (command == keyWarpDec) {
      unsetAbortFlag();
      Keyboard.begin();
      Keyboard.print(','); 
      Keyboard.end();
    }
    else if (command == keyCam) {
      unsetAbortFlag();
      Keyboard.begin();
      Keyboard.print('k'); 
      Keyboard.end();
    }
  }
}

void sendThrottle(int16_t throttle) {

  //to be sure to stay in integers range later
  throttle = constrain(throttle, 0, 100);
  
  //I use %, but KSP expects 0 -> 32767
  throttle = throttle * 327,67;
  
  mySimpit.send(THROTTLE_MESSAGE, (unsigned char*) &throttle, 2);
}

void sendRotation(int16_t pitch, int16_t yaw, int16_t roll) {

  rotationMessage myRotation;

  myRotation.pitch = pitch;
  myRotation.yaw = yaw;
  myRotation.roll = roll;
  myRotation.mask = 7;
  mySimpit.send(ROTATION_MESSAGE, myRotation);
}

void sendTranslation(int16_t x, int16_t y, int16_t z) {

  translationMessage myTranslation;
  
  myTranslation.X = x;
  myTranslation.Y = y;
  myTranslation.Z = z;
  myTranslation.mask = 7;
  mySimpit.send(TRANSLATION_MESSAGE, myTranslation);
}


char* checkCommand(uint32_t command, uint32_t value) {

  if ((millis() - previousComm) > CommDelay) {

    previousComm = millis();
    
    if (command == NIX) {
      return "NIX";
    }
    else if (command == acgStage) {
      unsetAbortFlag();
      return "activate Stage";
    }
    else if (command == acgAbort) {
      if (checkAbortFlag() || value == 0) {
        return "activate Abort";
      }
      else {
        return "NIX";
      }
    }
    else if (command == acgLight) {
      unsetAbortFlag();
      if (value == 0)
        return "deactivate Light";
      else if (value == 1)
        return "toggle Light";
      else if (value == 2)
        return "activate Light";
    }
    else if (command == acgGear) {
      unsetAbortFlag();
      if (value == 0)
        return "deactivate Gear";
      else if (value == 1)
        return "toggle Gear";
      else if (value == 2)
        return "activate Gear";
    }
    else if (command == acgBrakes) {
      unsetAbortFlag();
      if (value == 0)
        return "deactivate Brakes";
      else if (value == 1)
        return "toggle Brakes";
      else if (value == 2)
        return "activate Brakes";
    }
    else if (command == acgRCS) {
      unsetAbortFlag();
      if (value == 0)
        return "deactivate RCS";
      else if (value == 1)
        return "toggle RCS";
      else if (value == 2)
        return "activate RCS";
    }
    else if (command == acgSAS) {
      unsetAbortFlag();
      if (value == 0)
        return "deactivate SAS";
      else if (value == 1)
        return "toggle SAS";
      else if (value == 2)
        return "activate SAS";
    }
    else if (command == acg1 || command == acg2 || command == acg3 || command == acg4 || command == acg5 ||
             command == acg6 || command == acg7 || command == acg8 || command == acg9 || command == acg10){
      unsetAbortFlag();
      if (value == 0)
        return "deactivate ACG";
      else if (value == 1)
        return "toggle ACG";
      else if (value == 2)
        return "activate ACG";
    }
    else if (command == sasStability) {
      unsetAbortFlag();
      return "activate Stability";
    }
    else if (command == sasManeuver) {
      unsetAbortFlag();
      return "activate Maneuver";
    }
    else if (command == sasPrograde) {
      unsetAbortFlag();
      return "activate Prograde";
    }
    else if (command == sasRetrograde) {
      unsetAbortFlag();
      return "activate Retrograde";
    }
    else if (command == sasNormal) {
      unsetAbortFlag();
      return "activate Normal";
    }
    else if (command == sasAntinormal) {
      unsetAbortFlag();
      return "activate Antinormal";
    }
    else if (command == sasRadialin) {
      unsetAbortFlag();
      return "activate Radialin";
    }
    else if (command == sasRadialout) {
      unsetAbortFlag();
      return "activate Radialout";
    }
    else if (command == sasTarget) {
      unsetAbortFlag();
      return "activate Target";
    }
    else if (command == sasAntitarget) {
      unsetAbortFlag();
      return "activate Antitarget";
    }
    else if (command == setThrottle) {
      unsetAbortFlag();
      return "throttle";
    }
    else if (command == keyMap) {
      unsetAbortFlag();
      return ("keyMap: m");      
    }
    else if (command == keyWarpInc) {
      unsetAbortFlag();
      return ("keyWarpInc: ."); 
    }
    else if (command == keyWarpDec) {
      unsetAbortFlag();
      return ("keyWarpDec: ,"); 
    }
    else if (command == keyCam) {
      unsetAbortFlag();
      return ("keyCam: k"); 
    }
  }
  else {
    return "debounce";
  }
}
