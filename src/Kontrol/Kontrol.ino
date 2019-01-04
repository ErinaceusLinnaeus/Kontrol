 /* (C)2018 Benjamin Schmid

   Kontrol is an Arduino Project to control KSP.
   The hardware includes two 3-axis-joysticks, a keyboard, a 12" HDMI Display, a 10" resistiv touchpanel.
   Interfacing with KSP through KerbalSimPit, an Arduino library written by Peter Hardy.
*/

//Including my own libraries
#include "AutoRocket.h"
#include "DisplayOperations.h"
#include "send.h"


//Create the AutoRocketList. For now only one wil ever be used.
//Loading or starting a new one will unload the current Script.
//Acronym for AutoRocketList; isn't it cute?
AutoRocketList auroli;


void setup() {

  Serial.begin(115200);
  
  initializeDisplay();

  delay(1000);
  auroli.setFilename("Go Rocket, go.");
  auroli.setDescription("Just playing around...");

  auroli.newNode(setThrottle, 80, "Some Throttle!");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(setThrottle, 20, "Fewer Throttle!");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(setThrottle, 100, "Full Throttle!");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(setThrottle, 0, "No Throttle!");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  
  auroli.newNode(toggleACG, acgStage, "Staging");

  auroli.newNode(waitTenthSeconds, 30, "HICKS!");
  
  auroli.newNode(toggleACG, acgLight, "Light");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(toggleACG, acgGear, "Gear");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(toggleACG, acgBrakes, "Brakes");

  auroli.newNode(waitTenthSeconds, 30, "HICKS!");
  
  auroli.newNode(toggleACG, acgSAS, "SAS");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(toggleACG, acgRCS, "RCS");
  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  auroli.newNode(toggleACG, acgAbort, "Abort");

  auroli.newNode(waitTenthSeconds, 30, "HICKS!");
  
  auroli.newNode(toggleACG, acg1, "1");

  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  
  auroli.newNode(toggleACG, acg2, "2");

  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  
  auroli.newNode(toggleACG, acg3, "3");

  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  
  auroli.newNode(toggleACG, acg4, "4");

  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  
  auroli.newNode(toggleACG, acg5, "5");

  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  
  auroli.newNode(toggleACG, acg6, "6");

  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  
  auroli.newNode(toggleACG, acg7, "7");

  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  
  auroli.newNode(toggleACG, acg8, "8");

  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  
  auroli.newNode(toggleACG, acg9, "9");

  auroli.newNode(waitTenthSeconds, 10, "HICKS!");
  
  auroli.newNode(toggleACG, acg0, "0");
  
  auroli.newNode(waitTenthSeconds, 30, "HICKS!");
    
  printList(auroli);
  delay(3000);
  
/*
  delay(1000);
  auroli.delNode();
  printList(auroli);
*/
/*
  delay(1000);
  auroli.goToNextNode();
  printList(auroli);
*/


  initializeSimpit();
  
  delay(1000);
  auroli.goToTheTop();
  printList(auroli);
}

void loop() {

  updateSimpit();
  auroli.launchList();
}
