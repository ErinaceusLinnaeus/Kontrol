 /* (C)2018 Benjamin Schmid

   Kontrol is an Arduino Project to control KSP.
   The hardware includes two 3-axis-joysticks, a keyboard, a 12" HDMI Display, a 10" resistiv touchpanel.
   Interfacing with KSP through KerbalSimPit, an Arduino library written by Peter Hardy.
*/

//Including my own libraries
#include "AutoRocket.h"
#include "DisplayOperations.h"


//Create the AutoRocketList. For now only one wil ever be used.
//Loading or starting a new one will unload the current Script.
//Acronym for AutoRocketList; isn't it cute?
AutoRocketList auroli;



void setup() {

  Serial.begin(115200);

  initializeDisplay();

  delay(1000);
  printList(auroli);

  delay(1000);
  auroli.newNode(setThrottle, 100, "Full Throttle!");
  printList(auroli);

  delay(1000);
  auroli.newNode(setStage, 1, "Staging");
  printList(auroli);

  delay(1000);
  auroli.newNode(toggleACG, 4, "Action Group 4.");
  printList(auroli);

  delay(1000);
  auroli.delNode();
  printList(auroli);

  delay(1000);
  auroli.goToTheTop();
  printList(auroli);
}

void loop() {

}
