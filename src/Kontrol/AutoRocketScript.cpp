/* (C)2018 Benjamin Schmid  
 *  
 *  AutoRocketScript.cpp
 */

#include "AutoRocketScript.h"
#include <string.h>

void AutoRocketScript::newScript(char filename[15], char description[255]) {

  strcpy(filename, filename);
  strcpy(description, description);

  saveScript();
}

//Save to SD Card
void AutoRocketScript::saveScript() {
  
}



void AutoRocketNode::newNode() {

  uint32_t command;
  char message[127];
  
  editCommand(command);
  editCommand(*message);
}

void AutoRocketNode::editCommand(uint32_t a) {

  command = a;
}

void AutoRocketNode::editMessage(char a[127]) {

  strcpy(message, a);
}
