/* (C)2018 Benjamin Schmid
 * 
 * Kontrol is an Arduino Project to control KSP.
 * The hardware includes two 3-axis-joysticks, a keyboard, a 7" HDMI Display and a 10" resistiv touchpanel.
 * Getting Information from the keyboard through USBHost, an Arduino library.
 * Interfacing with KSP through KerbalSimPit, an Arduino library written by Peter Hardy.
 */

#include <KeyboardController.h>
#include "AutoRocketScript.h"

//Initializing the USB HostController
USBHost usb;

//Attach mouse controller
KeyboardController keyboard(usb);


//The Keyboard writes in here
char KeyboardBuffer[127] = "";

// This function intercepts key press
void keyPressed() {
  fillKeyboardBuffer();
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


void setup() {

  Serial.begin(115200);
  Serial.println("setup");
  
}

void loop() {

  usb.Task();

}
