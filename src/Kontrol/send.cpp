

#include "send.h"

//KerbalSimPit
#include <KerbalSimpit.h>
#include <KerbalSimpitMessageTypes.h>
#include <PayloadStructs.h>

// Declare a KerbalSimpit object that will
// communicate using the "Serial" device.
KerbalSimpit mySimpit(Serial);

rotationMessage myRotation;
translationMessage myTranslation;
AutopilotMode mySASMode;

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

void sendACG(uint32_t acg) {

  if (acg == acgStage)
    mySimpit.activateAction(STAGE_ACTION);
  else if (acg == acgAbort)
    mySimpit.activateAction(ABORT_ACTION);
  else if (acg == acgLight)
    mySimpit.toggleAction(LIGHT_ACTION);
  else if (acg == acgGear)
    mySimpit.toggleAction(GEAR_ACTION);
  else if (acg == acgBrakes)
    mySimpit.toggleAction(BRAKES_ACTION);
  else if (acg == acgRCS)
    mySimpit.toggleAction(RCS_ACTION);
  else if (acg == acgSAS)
    mySimpit.toggleAction(SAS_ACTION);
  else
    mySimpit.toggleCAG(acg);
}

void sendSAS(uint32_t sas) {
/*
  if (sas == sasStability)
    mySASMode = AP_STABILITYASSIST;
  else if (sas == sasManeuver)
    mySASMode = AP_MANEUVER;
  else if (sas == sasPrograde)
    mySASMode = AP_PROGRADE;
  else if (sas == sasRetrograde)
    mySASMode = AP_RETROGRADE;
  else if (sas == sasNormal)
    mySASMode = AP_NORMAL;
  else if (sas == sasAntinormal)
    mySASMode = AP_ANTINORMAL;
  else if (sas == sasRadialin)
    mySASMode = AP_RADIALIN;
  else if (sas == sasRadialout)
    mySASMode = AP_RADIALOUT;
  else if (sas == sasTarget)
    mySASMode = AP_TARGET;
  else if (sas == sasAntitarget)
    mySASMode = AP_ANTITARGET;
    
//  mySimpit.send(SAS_MODE_MESSAGE, mySASMode, 1);
  mySimpit.send(SAS_MODE_MESSAGE, mySASMode);
*/

  if (sas == sasStability)
    mySimpit.setSASMode(AP_STABILITYASSIST);
  else if (sas == sasManeuver)
    mySimpit.setSASMode(AP_MANEUVER);
  else if (sas == sasPrograde)
    mySimpit.setSASMode(AP_PROGRADE);
  else if (sas == sasRetrograde)
    mySimpit.setSASMode(AP_RETROGRADE);
  else if (sas == sasNormal)
    mySimpit.setSASMode(AP_NORMAL);
  else if (sas == sasAntinormal)
    mySimpit.setSASMode(AP_ANTINORMAL);
  else if (sas == sasRadialin)
    mySimpit.setSASMode(AP_RADIALIN);
  else if (sas == sasRadialout)
    mySimpit.setSASMode(AP_RADIALOUT);
  else if (sas == sasTarget)
    mySimpit.setSASMode(AP_TARGET);
  else if (sas == sasAntitarget)
    mySimpit.setSASMode(AP_ANTITARGET);
}

void sendThrottle(int16_t throttle) {

  //I use %, but KSP expects 0 -> 32767
  throttle = throttle * 327,67;
  mySimpit.send(THROTTLE_MESSAGE, (unsigned char*) &throttle, 2);
}

void sendRotation(int16_t pitch, int16_t yaw, int16_t roll) {

  myRotation.pitch = pitch;
  myRotation.yaw = yaw;
  myRotation.roll = roll;
  myRotation.mask = 7;
  mySimpit.send(ROTATION_MESSAGE, myRotation);
}

void sendTranslation(int16_t x, int16_t y, int16_t z) {

  myTranslation.X = x;
  myTranslation.Y = y;
  myTranslation.Z = z;
  myTranslation.mask = 7;
  mySimpit.send(TRANSLATION_MESSAGE, myTranslation);
}
