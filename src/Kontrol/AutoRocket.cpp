/* (C)2018 Benjamin Schmid  
 *  
 *  AutoRocket.cpp
 */

#include "AutoRocket.h"
#include <string.h>

char* getTodosString(todos action){
  
  switch(action){
      case 0:
        return"waitTenthSeconds";
      case 1:
       return "waitForDistanceCM";
      case 2:
       return "waitForRAltM";
      case 3:
       return "waitForAltM";
      case 4:
       return "waitForAltKM";
      case 5:
       return "setThrottle";
      case 6:
       return "setStage";
      case 7:
       return "toggleACG";
      case 8:
       return "setAttitude";
      case 9:
       return "setTranslation";
      case 10:
       return "theExitNode";
      default:
       return "outOfRange";
    }
}


AutoRocketList::AutoRocketList() {

  this->setFilename("newScript");
  this->setDescription("Describe me...");

  this->firstNode = new AutoRocketNode();
  this->lastNode = new AutoRocketNode(theExitNode, 0);
  
  this->firstNode->prevNode = NULL;
  this->firstNode->nextNode = this->lastNode;
  
  this->lastNode->prevNode = this->firstNode;
  this->lastNode->nextNode = NULL;

  this->currNode = firstNode;

//  saveScript();
}

//Save to SD Card
void AutoRocketList::saveScript() {

  NULL;
}


//Default Constructor creates a 3sec waiting node
AutoRocketNode::AutoRocketNode() {

  //Defining default values for the first node
  this->action = waitTenthSeconds;
  this->value = 30;
}

//Constructing a Node
AutoRocketNode::AutoRocketNode(todos action, uint32_t value) {

  this->action = action;
  this->value = value;
}

void AutoRocketNode::newNode(AutoRocketNode *currNode, todos action, uint32_t value) {

  AutoRocketNode* temp;
  temp = new AutoRocketNode();
  
  temp->action = action;
  temp->value = value;
  
  temp->prevNode = currNode;
  temp->nextNode = currNode->nextNode;
  currNode->nextNode = temp;
  temp->nextNode->prevNode = temp;
}

void AutoRocketNode::delNode(AutoRocketNode *node) {
  
  node->prevNode->nextNode = node->nextNode;
  node->nextNode->prevNode = node->prevNode;

  delete node;
}

todos AutoRocketNode::getAction() {
  
  return this->action;
}

uint32_t AutoRocketNode::getValue() {
  
  return this->value;
}

char* AutoRocketList::getFilename(){

  return this->filename;
}

char* AutoRocketList::getDescription(){
  
  return this->description;
}

void AutoRocketList::setFilename(char filename[15]) {
  
  strcpy(this->filename, filename);
//  saveScript();
}


void AutoRocketList::setDescription(char description[255]) {
  
  strcpy(this->description, description);
//  saveScript();
}
