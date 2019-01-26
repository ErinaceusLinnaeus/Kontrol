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
  
  auroli.newNode(setRotationPitch, 512, "RotationPitch");
  auroli.newNode(setRotationYaw, 512, "RotationYaw");
  auroli.newNode(setRotationRoll, 512, "RotationRoll");
  auroli.newNode(setTranslationX, 512, "TranslationX");
  auroli.newNode(setTranslationY, 512, "TranslationY");
  auroli.newNode(setTranslationZ, 512, "TranslationZ");

  Nonworking, so far:

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

  auroli.newNode(toggleACG, acgLight, "Light");
  auroli.newNode(setSAS, sasStability, "Stability");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(toggleACG, acgLight, "Light");
  auroli.newNode(setSAS, sasManeuver, "Maneuver");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(toggleACG, acgLight, "Light");
  auroli.newNode(setSAS, sasPrograde, "Prograde");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(toggleACG, acgLight, "Light");
  auroli.newNode(setSAS, sasRetrograde, "Retrograde");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(toggleACG, acgLight, "Light");
  auroli.newNode(setSAS, sasNormal, "Normal");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(toggleACG, acgLight, "Light");
  auroli.newNode(setSAS, sasAntinormal, "Antinormal");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(toggleACG, acgLight, "Light");
  auroli.newNode(setSAS, sasRadialin, "Radial In");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(toggleACG, acgLight, "Light");
  auroli.newNode(setSAS, sasRadialout, "Radial Out");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(toggleACG, acgLight, "Light");
  auroli.newNode(setSAS, sasTarget, "Target");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(toggleACG, acgLight, "Light");
  auroli.newNode(setSAS, sasAntitarget, "Antitarget");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
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
  sendRotation(getSASpitch(), getSASyaw(), getSASroll());
  sendTranslation(getRCSx(), getRCSy(), getRCSz());
  
//  delay(500);
  auroli.launchList();
}
