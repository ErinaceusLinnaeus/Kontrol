

#include "send.h"

//KerbalSimPit
#include <KerbalSimpit.h>
#include <KerbalSimpitMessageTypes.h>
#include <PayloadStructs.h>

// Declare a KerbalSimpit object that will
// communicate using the "Serial" device.
KerbalSimpit mySimpit(Serial);


void initializeSimpit() {
      
  // This loop continually attempts to handshake with the plugin.
  // It will keep retrying until it gets a successful handshake.
  while (!mySimpit.init());
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
  //Doesn't compile SAS_MODE_MESSAGE & AP_... are not declared in this scope
  if (sas == sasStability)
    mySimpit.send(SAS_MODE_MESSAGE, AP_STABILITYASSIST, 1);
  else if (sas == sasManeuver)
    mySimpit.send(SAS_MODE_MESSAGE, AP_PROGRADE, 1);
  else if (sas == sasPrograde)
    mySimpit.send(SAS_MODE_MESSAGE, AP_RETROGRADE, 1);
  else if (sas == sasRetrograde)
    mySimpit.send(SAS_MODE_MESSAGE, AP_NORMAL, 1);
  else if (sas == sasNormal)
    mySimpit.send(SAS_MODE_MESSAGE, AP_ANTINORMAL, 1);
  else if (sas == sasAnti)
    mySimpit.send(SAS_MODE_MESSAGE, AP_RADIALIN, 1);
  else if (sas == sasRadialin)
    mySimpit.send(SAS_MODE_MESSAGE, AP_RADIALOUT, 1);
  else if (sas == sasRadialout)
    mySimpit.send(SAS_MODE_MESSAGE, AP_TARGET, 1);
  else if (sas == sasTarget)
    mySimpit.send(SAS_MODE_MESSAGE, AP_ANTITARGET, 1);
  else if (sas == sasAntitarget)
    mySimpit.send(SAS_MODE_MESSAGE, AP_MANEUVER, 1);*/
}

void sendThrottle(uint32_t throttle) {

  //Doesn't work!
  mySimpit.send(THROTTLE_MESSAGE, (unsigned char*) &throttle, 2);
}
