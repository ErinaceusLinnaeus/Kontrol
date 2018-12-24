/* (C)2018 Benjamin Schmid

   Kontrol is an Arduino Project to control KSP.
   The hardware includes two 3-axis-joysticks, a keyboard, a 12" HDMI Display, a 10" resistiv touchpanel.
   Getting Information from the keyboard through USBHost, an Arduino library.
   Interfacing with KSP through KerbalSimPit, an Arduino library written by Peter Hardy.
*/

//#include <SPI.h>
#include <KeyboardController.h>
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

//Initializing the USB HostController
USBHost usb;

//Attach mouse controller
KeyboardController keyboard(usb);

//The Keyboard writes in here
char KeyboardBuffer[127] = "";
bool captureKeyboard = true;

// This function intercepts key press
void keyPressed() {
  if (captureKeyboard) {
    fillKeyboardBuffer();
  }
}

void fillKeyboardBuffer() {

  // getOemKey() returns the OEM-code associated with the key
  //  Serial.print(keyboard.getOemKey());


  //Delete is pressed and the buffer is not empty
  if (keyboard.getOemKey() == 42 && strlen(KeyboardBuffer) > 0) {
    KeyboardBuffer[strlen(KeyboardBuffer) - 1] = '\0';
  }
  //Enter is pressed and the buffer is not empty
  else if (keyboard.getOemKey() == 40) {
    if (strlen(KeyboardBuffer) != 0) {
      strcat(KeyboardBuffer, "\n");
    }
  }
  //fill the buffer
  else {
    KeyboardBuffer[strlen(KeyboardBuffer)] = keyboard.getKey();
  }

  Serial.println(KeyboardBuffer);
}

int fontPosX = 10;
int fontPosY = 10;

void printList(AutoRocketList auroli) {

  tft.drawString(auroli.getFilename(), 20, 20, GFXFF);
  tft.drawString(auroli.getDescription(), 20, 40, GFXFF);

  AutoRocketNode* temp = auroli.firstNode;

  int i = 60;

  while (temp->nextNode != NULL) {
    
    switch(temp->getAction()){
      case 0:
        tft.drawString(" 0: waitTenthSeconds", 40, i, GFXFF);
        break;
      case 1:
        tft.drawString(" 1: waitForDistanceCM", 40, i, GFXFF);
        break;
      case 2:
        tft.drawString(" 2: waitForRAltM", 40, i, GFXFF);
        break;
      case 3:
        tft.drawString(" 3: waitForAltM", 40, i, GFXFF);
        break;
      case 4:
        tft.drawString(" 4: waitForAltKM", 40, i, GFXFF);
        break;
      case 5:
        tft.drawString(" 5: setThrottle", 40, i, GFXFF);
        break;
      case 6:
        tft.drawString(" 6: setStage", 40, i, GFXFF);
        break;
      case 7:
        tft.drawString(" 7: toggleACG", 40, i, GFXFF);
        break;
      case 8:
        tft.drawString(" 8: setAttitude", 40, i, GFXFF);
        break;
      case 9:
        tft.drawString(" 9: setTranslation", 40, i, GFXFF);
        break;
      case 10:
        tft.drawString("10: theExitNode", 40, i, GFXFF);
        break;
    }
    
    tft.drawNumber(temp->getValue(), 60, i + 20, GFXFF);
    temp = temp->nextNode;
    
    i += 40;
  }
  
  tft.drawString("10: theExitNode", 40, i, GFXFF);
  tft.drawNumber(temp->getValue(), 60, i + 20, GFXFF);
}

void setup() {

  Serial.begin(115200);

  Serial.println(auroli.getFilename());
  Serial.println(auroli.getDescription());

  //Setup the LCD
  tft.begin();

  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.setFreeFont(FM9);



  printList(auroli);

  

}

void loop() {

  usb.Task();

  tft.drawString(KeyboardBuffer, fontPosY, fontPosX, GFXFF);

  if (keyboard.getOemKey() == 40) {
    fontPosX += 15;
  }

}
