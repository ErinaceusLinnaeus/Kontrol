

#include "send.h"

//KerbalSimPit
#include <KerbalSimpit.h>
#include <KerbalSimpitMessageTypes.h>
#include <PayloadStructs.h>

// Declare a KerbalSimpit object that will
// communicate using the "Serial" device.
KerbalSimpit mySimpit(Serial);

rotationMessage myAttitude;

void initializeSimpit() {
      
  // This loop continually attempts to handshake with the plugin.
  // It will keep retrying until it gets a successful handshake.
  while (!mySimpit.init());

  //needed to send throttle
  mySimpit.registerChannel(THROTTLE_MESSAGE);
  //needed to send attitude
  mySimpit.registerChannel(ROTATION_MESSAGE);
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

  if (sas == sasStability)
    mySimpit.setSASMode(AP_STABILITYASSIST);
  else if (sas == sasManeuver)
    mySimpit.setSASMode(AP_PROGRADE);
  else if (sas == sasPrograde)
    mySimpit.setSASMode(AP_RETROGRADE);
  else if (sas == sasRetrograde)
    mySimpit.setSASMode(AP_NORMAL);
  else if (sas == sasNormal)
    mySimpit.setSASMode(AP_ANTINORMAL);
  else if (sas == sasAntinormal)
    mySimpit.setSASMode(AP_RADIALIN);
  else if (sas == sasRadialin)
    mySimpit.setSASMode(AP_RADIALOUT);
  else if (sas == sasRadialout)
    mySimpit.setSASMode(AP_TARGET);
  else if (sas == sasTarget)
    mySimpit.setSASMode(AP_ANTITARGET);
  else if (sas == sasAntitarget)
    mySimpit.setSASMode(AP_MANEUVER);
}

void sendThrottle(int16_t throttle) {

  //I use %, but KSP expects 0 -> 32767
  throttle = throttle * 327,67;
  mySimpit.send(THROTTLE_MESSAGE, (unsigned char*) &throttle, 2);
}

void sendAttitude(int16_t pitch, int16_t yaw, int16_t roll) {

  myAttitude.pitch = pitch;
  myAttitude.yaw = yaw;
  myAttitude.roll = roll;
  mySimpit.send(ROTATION_MESSAGE, myAttitude);
}
