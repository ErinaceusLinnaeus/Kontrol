/* (C)2018 Benjamin Schmid
 * 
 * Kontrol is an Arduino Project to control KSP.
 * The hardware includes two 3-axis-joysticks, a keyboard, a 12" HDMI Display, a 10" resistiv touchpanel.
 * Getting Information from the keyboard through USBHost, an Arduino library.
 * Interfacing with KSP through KerbalSimPit, an Arduino library written by Peter Hardy.
 */

//#include <SPI.h>
#include <KeyboardController.h>
#include "AutoRocketScript.h"
//Display
#include <TFT_HX8357_Due.h>
//Part of the All_Free_Fonts_Demo of the TFT library
#include "Free_Fonts.h"

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
    KeyboardBuffer[strlen(KeyboardBuffer)-1] = '\0';
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
  
void setup() {

  Serial.begin(115200);
  
  //Setup the LCD
  tft.begin();

  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.setFreeFont(FM9);

}

void loop() {

  usb.Task();
  
  tft.drawString(KeyboardBuffer, fontPosY, fontPosX, GFXFF);

  if (keyboard.getOemKey() == 40) {
    fontPosX += 15;
  }

}
