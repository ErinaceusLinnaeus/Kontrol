/* (C)2018 Benjamin Schmid

  Kontrol is an Arduino Project to control KSP.
  The hardware includes two 3-axis-joysticks, a keyboard, a 12" HDMI Display, a 10" resistiv touchpanel.
  Interfacing with KSP through KerbalSimPit, an Arduino library written by Peter Hardy.
*/

/*
  Things that do work:

  auroli.setFilename("Go Rocket, go.");
  auroli.setDescription("Just playing around...");
  auroli.delNode();
  auroli.goToTheTop();

  printList(auroli);

  auroli.newNode(waitTenthSeconds, 10, "HICKS!");

  auroli.newNode(toggleACG, acgStage, "Staging");

  auroli.newNode(toggleACG, acgSAS, "SAS");
  auroli.newNode(toggleACG, acgRCS, "RCS");

  auroli.newNode(toggleACG, acgLight, "Light");
  auroli.newNode(toggleACG, acgGear, "Gear");
  auroli.newNode(toggleACG, acgBrakes, "Brakes");
  auroli.newNode(toggleACG, acgAbort, "Abort");

  auroli.newNode(toggleACG, acg1, "1");
  auroli.newNode(toggleACG, acg2, "2");
  auroli.newNode(toggleACG, acg3, "3");
  auroli.newNode(toggleACG, acg4, "4");
  auroli.newNode(toggleACG, acg5, "5");
  auroli.newNode(toggleACG, acg6, "6");
  auroli.newNode(toggleACG, acg7, "7");
  auroli.newNode(toggleACG, acg8, "8");
  auroli.newNode(toggleACG, acg9, "9");
  auroli.newNode(toggleACG, acg10, "10");
  
  auroli.newNode(setThrottle, 80, "Some Throttle!");

  Nonworking, so far:

  auroli.newNode(toggleACG, acgSAS, "SAS");
  auroli.newNode(setSAS, sasStability, "Stability");
  auroli.newNode(setSAS, sasManeuver, "Maneuver");
  auroli.newNode(setSAS, sasPrograde, "Prograde");
  auroli.newNode(setSAS, sasRetrograde, "Retrograde");
  auroli.newNode(setSAS, sasNormal, "Normal");
  auroli.newNode(setSAS, sasAntinormal, "Antinormal");
  auroli.newNode(setSAS, sasRadialin, "Radial In");
  auroli.newNode(setSAS, sasRadialout, "Radial Out");
  auroli.newNode(setSAS, sasTarget, "Target");
  auroli.newNode(setSAS, sasAntitarget, "Antitarget");
  
  auroli.newNode(setAttitude, 512, "Attitude");
*/


//Including my own libraries
#include "AutoRocket.h"
#include "DisplayOperations.h"
#include "send.h"
#include "joysticks.h"

//Create the AutoRocketList. Only one will ever be used.
//Loading or starting a new one will unload the current Script.
//Acronym for AutoRocketList; isn't it cute?
AutoRocketList auroli;


void setup() {

  Serial.begin(115200);

  initializePins();
//  initializeDisplay();
  initializeSimpit();
}

void loop() {

  updateSimpit();

/*
  
  Serial.println("---");
  Serial.println("---");
    
  Serial.print("pitch : ");
  Serial.println(getSASpitch());
  Serial.print("yaw   : ");
  Serial.println(getSASyaw());
  Serial.print("roll  : ");
  Serial.println(getSASroll());

  Serial.print("x     : ");
  Serial.println(getRCSx());
  Serial.print("y     : ");
  Serial.println(getRCSy());
  Serial.print("z     : ");
  Serial.println(getRCSz());
*/

  sendAttitude(getSASpitch(), getSASyaw(), getSASroll());
  sendTranslation(getRCSx(), getRCSy(), getRCSz());
  
  delay(500);
  auroli.launchList();
}
