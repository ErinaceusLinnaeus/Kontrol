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

    todos action;
    uint32_t value;
  
  editNode(action, value);
}

void AutoRocketNode::editNode(todos a, uint32_t v) {

  action = a;
  value = v;
}
