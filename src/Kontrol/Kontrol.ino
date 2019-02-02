/* (C)2019 Benjamin Schmid
 *  
 *  Kontrol is an Arduino Project to control KSP.
 *  The hardware includes two 3-axis-joysticks, a 12" HDMI Display, a 10" resistiv touchpanel.
 *  Interfacing with KSP through KerbalSimPit, an Arduino library written by Peter Hardy.
 */

//If 0: The connection to Simpit will be established -> Jibberish on serial monitor
//If 1: To debug joystick and touchscreen coordinates
//If 2: To debug touchscreen field replies
#define DEBUG 0

//Including my own libraries
#include "AutoRocket.h"
#include "communication.h"
#include "DisplayOperations.h"
#include "joysticks.h"
#include "touch.h"

//Create the AutoRocketList. Only one will ever be used.
//Loading or starting a new one will unload the current Script.
//Acronym for AutoRocketList; isn't it cute?
AutoRocketList auroli;

//Create a touchpanel object
TouchPanel touchy;

//This is needed by an array to determine what command to send when touching a specific field
command TouchScreenField[9][11] = {NIX};
//The actual function is at the bottom, because it's really ugly
void fillTouchScreenField();

void setup() {

  Serial.begin(115200);
  fillTouchScreenField();
  
  initializeJoystickPins();
//  initializeDisplay();

  if (DEBUG == 0)
    initializeSimpit();
}

void loop() {
  
  if (DEBUG == 0) {
    updateSimpit();
    sendRotation(getSASpitch(), getSASyaw(), getSASroll());
    sendTranslation(getRCSx(), getRCSy(), getRCSz());
    // Getting the right commd in the matrix
    command tmp = TouchScreenField[touchy.getStoreyX()][touchy.getStoreyY()];

    //There's this throttle slide...
    if (tmp == setThrottle) {
      sendCommand(tmp, map(touchy.getPreciseX(), 200, 600, 0, 100));
    }
    //...else it's just buttons
    else {
      // 1 is to toggle
      sendCommand(tmp, 1);
    }
  }
  else if (DEBUG == 1) {
    checkJoysticks();
    touchy.check();
  }
  else if (DEBUG == 2) {
// Getting the right commd in the matrix
    command tmp = TouchScreenField[touchy.getStoreyX()][touchy.getStoreyY()];

    Serial.print(checkCommand(tmp, 1));
    Serial.print(" : ");
    if (tmp == setThrottle) {
      Serial.println(map(touchy.getPreciseX(), 200, 600, 0, 100));
    }
    else {
      // 1 is to toggle
      Serial.println("1");
    }
//    Serial.println("------------------------");
    delay(250);
  }
    


}


void fillTouchScreenField() {

  TouchScreenField[0][0] = NIX;
  
  TouchScreenField[1][1] = acgAbort;
  TouchScreenField[1][2] = acgAbort;
  TouchScreenField[1][3] = acgRCS;
  TouchScreenField[1][4] = acgRCS;
  TouchScreenField[1][5] = acgStage;
  TouchScreenField[1][6] = acgStage;
  TouchScreenField[1][7] = acgStage;
  TouchScreenField[1][8] = acgStage;
  TouchScreenField[1][9] = acgBrakes;
  TouchScreenField[1][10] = acgAbort;
  
  TouchScreenField[2][1] = NIX;
  TouchScreenField[2][2] = setThrottle;
  TouchScreenField[2][3] = NIX;
  TouchScreenField[2][4] = NIX;
  TouchScreenField[2][5] = NIX;
  TouchScreenField[2][6] = NIX;
  TouchScreenField[2][7] = NIX;
  TouchScreenField[2][8] = NIX;
  TouchScreenField[2][9] = acgLight;
  TouchScreenField[2][10] = acgGear;
  
  TouchScreenField[3][1] = NIX;
  TouchScreenField[3][2] = setThrottle;
  TouchScreenField[3][3] = NIX;
  TouchScreenField[3][4] = NIX;
  TouchScreenField[3][5] = NIX;
  TouchScreenField[3][6] = NIX;
  TouchScreenField[3][7] = NIX;
  TouchScreenField[3][8] = NIX;
  TouchScreenField[3][9] = sasTarget;
  TouchScreenField[3][10] = sasAntitarget;
  
  TouchScreenField[4][1] = NIX;
  TouchScreenField[4][2] = setThrottle;
  TouchScreenField[4][3] = NIX;
  TouchScreenField[4][4] = NIX;
  TouchScreenField[4][5] = NIX;
  TouchScreenField[4][6] = NIX;
  TouchScreenField[4][7] = NIX;
  TouchScreenField[4][8] = NIX;
  TouchScreenField[4][9] = sasRadialin;
  TouchScreenField[4][10] = sasRadialout;
  
  TouchScreenField[5][1] = NIX;
  TouchScreenField[5][2] = setThrottle;
  TouchScreenField[5][3] = NIX;
  TouchScreenField[5][4] = NIX;
  TouchScreenField[5][5] = NIX;
  TouchScreenField[5][6] = NIX;
  TouchScreenField[5][7] = NIX;
  TouchScreenField[5][8] = NIX;
  TouchScreenField[5][9] = sasNormal;
  TouchScreenField[5][10] = sasAntinormal;
 
  TouchScreenField[6][1] = NIX;
  TouchScreenField[6][2] = setThrottle;
  TouchScreenField[6][3] = NIX;
  TouchScreenField[6][4] = NIX;
  TouchScreenField[6][5] = NIX;
  TouchScreenField[6][6] = NIX;
  TouchScreenField[6][7] = NIX;
  TouchScreenField[6][8] = NIX;
  TouchScreenField[6][9] = sasPrograde;
  TouchScreenField[6][10] = sasRetrograde;
  
  TouchScreenField[7][1] = NIX;
  TouchScreenField[7][2] = setThrottle;
  TouchScreenField[7][3] = NIX;
  TouchScreenField[7][4] = NIX;
  TouchScreenField[7][5] = NIX;
  TouchScreenField[7][6] = NIX;
  TouchScreenField[7][7] = NIX;
  TouchScreenField[7][8] = NIX;
  TouchScreenField[7][9] = sasStability;
  TouchScreenField[7][10] = sasManeuver;

  TouchScreenField[8][1] = acg1;
  TouchScreenField[8][2] = acg2;
  TouchScreenField[8][3] = acg3;
  TouchScreenField[8][4] = acg4;
  TouchScreenField[8][5] = acg5;
  TouchScreenField[8][6] = acg6;
  TouchScreenField[8][7] = acg7;
  TouchScreenField[8][8] = acg8;
  TouchScreenField[8][9] = acg9;
  TouchScreenField[8][10] = acg10;
}
