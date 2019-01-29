/*  (C)2018 Benjamin Schmid
 *   
 *  DisplayOperations.cpp
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
