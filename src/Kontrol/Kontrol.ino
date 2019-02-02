/* (C)2019 Benjamin Schmid
 *  
 *  Kontrol is an Arduino Project to control KSP.
 *  The hardware includes two 3-axis-joysticks, a 12" HDMI Display, a 10" resistiv touchpanel.
 *  Interfacing with KSP through KerbalSimPit, an Arduino library written by Peter Hardy.
 */

//If 0: The connection to Simpit will be established -> Jibberish on serial monitor
//If 1: To debug joystick, touchscreen coordinates and the field
#define DEBUG 0

//Including my own libraries
#include "autorocketlist.h"
#include "communication.h"
#include "display.h"
#include "joysticks.h"
#include "touch.h"

//Create the AutoRocketList. Only one will ever be used.
//Loading or starting a new one will unload the current Script.
//Acronym for AutoRocketList; isn't it cute?
AutoRocketList auroli;

//Create a touchpanel object
TouchPanel touchy;

//Create a display object
Display hdmi;

//This is needed by an array to determine what command to send when touching a specific field
command commandMatrix[9][11] = {NIX};
//The actual function is at the bottom, because it's really ugly
void fillcommandMatrix();
void checkcommandMatrix();

void setup() {

  Serial.begin(115200);
  fillcommandMatrix();
  
  initializeJoystickPins();
  hdmi.initialize();

  if (DEBUG == 0)
    initializeSimpit();
}

void loop() {
  
  if (DEBUG == 0) {
    updateSimpit();
    sendRotation(getSASpitch(), getSASyaw(), getSASroll());
    sendTranslation(getRCSx(), getRCSy(), getRCSz());
    // Getting the right commd in the matrix
    command tmp = commandMatrix[touchy.getStoreyX()][touchy.getStoreyY()];

    //There's this throttle slide...
    //The field 100->200 gives negative numbers
    //The field 600->700 gives numbers larger 100
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
    checkcommandMatrix();
    
    delay(200);
  }
    


}

void checkcommandMatrix() {
  // Getting the right commd in the matrix
  command tmp = commandMatrix[touchy.getStoreyX()][touchy.getStoreyY()];

  Serial.print(checkCommand(tmp, 1));
  if (tmp == setThrottle) {
    Serial.print(" : ");
    Serial.print(map(touchy.getPreciseX(), 200, 600, 0, 100));
  }
  Serial.println();
}

void fillcommandMatrix() {

  commandMatrix[0][0] = NIX;

  //starting in left bottm corner
  commandMatrix[1][1] = acgAbort;
  commandMatrix[1][2] = acgAbort;
  commandMatrix[1][3] = acgRCS;
  commandMatrix[1][4] = acgRCS;
  commandMatrix[1][5] = acgStage;
  commandMatrix[1][6] = acgStage;
  commandMatrix[1][7] = acgStage;
  commandMatrix[1][8] = acgStage;
  commandMatrix[1][9] = acgBrakes;
  commandMatrix[1][10] = acgAbort;
  
  commandMatrix[2][1] = NIX;
  commandMatrix[2][2] = setThrottle;
  commandMatrix[2][3] = NIX;
  commandMatrix[2][4] = NIX;
  commandMatrix[2][5] = NIX;
  commandMatrix[2][6] = NIX;
  commandMatrix[2][7] = NIX;
  commandMatrix[2][8] = NIX;
  commandMatrix[2][9] = acgLight;
  commandMatrix[2][10] = acgGear;
  
  commandMatrix[3][1] = NIX;
  commandMatrix[3][2] = setThrottle;
  commandMatrix[3][3] = NIX;
  commandMatrix[3][4] = NIX;
  commandMatrix[3][5] = NIX;
  commandMatrix[3][6] = NIX;
  commandMatrix[3][7] = NIX;
  commandMatrix[3][8] = NIX;
  commandMatrix[3][9] = sasTarget;
  commandMatrix[3][10] = sasAntitarget;
  
  commandMatrix[4][1] = NIX;
  commandMatrix[4][2] = setThrottle;
  commandMatrix[4][3] = NIX;
  commandMatrix[4][4] = NIX;
  commandMatrix[4][5] = NIX;
  commandMatrix[4][6] = NIX;
  commandMatrix[4][7] = NIX;
  commandMatrix[4][8] = NIX;
  commandMatrix[4][9] = sasRadialin;
  commandMatrix[4][10] = sasRadialout;
  
  commandMatrix[5][1] = NIX;
  commandMatrix[5][2] = setThrottle;
  commandMatrix[5][3] = NIX;
  commandMatrix[5][4] = NIX;
  commandMatrix[5][5] = NIX;
  commandMatrix[5][6] = NIX;
  commandMatrix[5][7] = NIX;
  commandMatrix[5][8] = NIX;
  commandMatrix[5][9] = sasNormal;
  commandMatrix[5][10] = sasAntinormal;
 
  commandMatrix[6][1] = NIX;
  commandMatrix[6][2] = setThrottle;
  commandMatrix[6][3] = NIX;
  commandMatrix[6][4] = NIX;
  commandMatrix[6][5] = NIX;
  commandMatrix[6][6] = NIX;
  commandMatrix[6][7] = NIX;
  commandMatrix[6][8] = NIX;
  commandMatrix[6][9] = sasPrograde;
  commandMatrix[6][10] = sasRetrograde;
  
  commandMatrix[7][1] = NIX;
  commandMatrix[7][2] = setThrottle;
  commandMatrix[7][3] = NIX;
  commandMatrix[7][4] = NIX;
  commandMatrix[7][5] = NIX;
  commandMatrix[7][6] = NIX;
  commandMatrix[7][7] = NIX;
  commandMatrix[7][8] = NIX;
  commandMatrix[7][9] = sasStability;
  commandMatrix[7][10] = sasManeuver;

  commandMatrix[8][1] = acg1;
  commandMatrix[8][2] = acg2;
  commandMatrix[8][3] = acg3;
  commandMatrix[8][4] = acg4;
  commandMatrix[8][5] = acg5;
  commandMatrix[8][6] = acg6;
  commandMatrix[8][7] = acg7;
  commandMatrix[8][8] = acg8;
  commandMatrix[8][9] = acg9;
  commandMatrix[8][10] = acg10;
}
