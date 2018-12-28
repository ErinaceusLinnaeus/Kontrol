/* (C)2018 Benjamin Schmid

   Kontrol is an Arduino Project to control KSP.
   The hardware includes two 3-axis-joysticks, a keyboard, a 12" HDMI Display, a 10" resistiv touchpanel.
   Interfacing with KSP through KerbalSimPit, an Arduino library written by Peter Hardy.
*/

#include "AutoRocket.h"
//Display
#include <TFT_HX8357_Due.h>
//Part of the All_Free_Fonts_Demo of the TFT library
#include "Free_Fonts.h"

//Create the AutoRocketList. For now only one wil ever be used.
//Loading or starting a new one will unload the current Script.
//Acronym for AutoRocketList; isn't it cute?
AutoRocketList auroli;


TFT_HX8357_Due tft = TFT_HX8357_Due(); // Invoke custom library

void printList(AutoRocketList auroli) {

  tft.drawString(auroli.getFilename(), 20, 20, GFXFF);
  tft.drawString(auroli.getDescription(), 20, 40, GFXFF);

  AutoRocketNode* temp = auroli.firstNode;

  int i = 60;

  while (temp != NULL) {

    if (temp == auroli.currNode){
      tft.drawString("*", 27, i+12, GFXFF);
    }

    tft.drawString(getTodosString(temp->getAction()), 40, i, GFXFF);
    tft.drawNumber(temp->getValue(), 40, i + 20, GFXFF);

    temp = temp->nextNode;
    i += 40;
  }
}

void setup() {

  Serial.begin(115200);
  
  //Setup the LCD
  tft.begin();

  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.setFreeFont(FM9);

  delay(1000);
  tft.fillScreen(TFT_BLACK);
  printList(auroli);

  delay(1000);
  tft.fillScreen(TFT_BLACK);
  auroli.newNode(auroli.currNode, setThrottle, 100);
  printList(auroli);

  delay(1000);
  tft.fillScreen(TFT_BLACK);
  auroli.newNode(auroli.currNode, setStage, 1);
  printList(auroli);

  delay(1000);
  tft.fillScreen(TFT_BLACK);
  auroli.newNode(auroli.currNode, toggleACG, 4);
  printList(auroli);
}

void loop() {

}
