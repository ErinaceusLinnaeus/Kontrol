/*  (C)2018 Benjamin Schmid
 *   
 *  DisplayOperations.cpp
 *  Functions to print things on the TFT Display
 */

//Display
#include <TFT_HX8357_Due.h>

#include "AutoRocket.h"

//Part of the All_Free_Fonts_Demo of the TFT library
#include "Free_Fonts.h"

TFT_HX8357_Due tft = TFT_HX8357_Due(); // Invoke custom library

void initializeDisplay(){
  
  //Setup the LCD
  tft.begin();

  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.setFreeFont(FM9);
}

void printBlack() {
  
  tft.fillScreen(TFT_BLACK);
}

void printInt(int i) {

  tft.drawNumber(i, 240, 100, GFXFF);
}


void printList(AutoRocketList auroli) {

  tft.fillScreen(TFT_BLACK);
  
  tft.drawString(auroli.getFilename(), 20, 20, GFXFF);
  tft.drawString(auroli.getDescription(), 20, 40, GFXFF);

  AutoRocketNode* temp = auroli.getFirstNode();

  int i = 70;

  //Printing also theExitNode
  while (temp != NULL) {
  //Not Printing theExitNode
  //while (temp->nextNode != NULL) {

    if (temp == auroli.getCurrNode()){
      tft.drawString("*", 22, i+2, GFXFF);//+22, GFXFF);
    }

    tft.drawString(getTodosString(temp->getAction()), 40, i, GFXFF);
    tft.drawNumber(temp->getValue(), 240, i, GFXFF);
//    tft.drawString(temp->getInformation(), 40, i+20, GFXFF);

    temp = temp->nextNode;
//    i += 50;
    i += 30;
  }
}
