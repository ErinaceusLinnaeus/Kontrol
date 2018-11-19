/*(C)2018 Benjamin Schmid
 * 
 * Kontrol is an Arduino Project to control KSP.
 * The hardware includes two 3-axis-joysticks, a keyboard, a 7" HDMI Display and a 10" resistiv touchpanel.
 * Getting Information from the keyboard through USBHost, an Arduino library.
 * Interfacing with KSP through KerbalSimPit, an Arduino library written by Peter Hardy.
 */

#include <KeyboardController.h>

//Initializing the USB HostController
USBHost usb;

//Attach mouse controller
KeyboardController keyboard(usb);

/*A datatype to program for autofly mode
 * First a name you can enter
 * And a description you can enter
 * Let the rocket wait or do some action?
 *  Wait for some time or till a given (radar)altitude?
 *  Take action:
 *    Throttle
 *    Stage
 *    Toggle an actiongroup
 *    Set an attitude - Steering
 *    Translate by RCS
 *  Value is either...
 *    ...the time [seconds]
 *    ...the (radar)altitude [meter]
 *    throttle [%]
 *    stage = 0
 *    actiongroup, also SAS, RCS, Brakes, Gear, etc.
 *      00000000 00000000 00000000 00000AAG - AG off
 *      00000000 00000000 00000000 00001AAG - AG on
 *    attitude
 *      00000000 00000000 0000000x xxyyyzzz
 *      x, y, z in planetary reference frame
 *    translate
 *      00000000 00000000 0000000x xxyyyzzz
 *      x: roll
 *      y: pitch
 *      z: yaw
 */
struct AutoRocketNode {
  enum command {
    wait,   //0
    action  //1
  };
  enum todo {
    sometime,       //0
    altitude,       //1
    radaraltitude,  //2
    throttle,       //3
    stage,          //4
    actiongroup,    //5
    attitude,       //6
    translate       //7
  };
  uint32_t value;
  struct AutoRocketNode *nextNode;
};
struct AutoRocketScript {
  char identifier[15];
  char description[127];
  struct AutoRocketNode *nextNode;
};

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
  AutoRocketScript rocket;
  
}

void loop() {

  usb.Task();

}
