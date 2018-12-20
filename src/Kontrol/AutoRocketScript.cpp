/* (C)2018 Benjamin Schmid  
 *  
 *  AutoRocketScript.cpp
 */

#include "AutoRocketScript.h"
#include <string.h>

AutoRocketScript::AutoRocketScript() {

  this->editFilename("newScript");
  this->editDescription("Describe me...");

  this->firstNode = new AutoRocketNode();
  this->lastNode = new AutoRocketNode(theExitNode, 0);
  this->firstNode->nextNode = this->lastNode;
  this->firstNode->prevNode = NULL;
  this->lastNode->prevNode = this->firstNode;
  this->lastNode->nextNode = NULL;

  this->currNode = firstNode;

  saveScript();
}

//Save to SD Card
void AutoRocketScript::saveScript() {

  NULL;
}


//Default Constructor creates a 3sec waiting node
AutoRocketNode::AutoRocketNode() {

  //Defining default values for the first node
  this->action = waitSeconds;
  this->value = 3;
}

//Constructing a Node
AutoRocketNode::AutoRocketNode(todos action, uint32_t value) {

  this->action = action;
  this->value = value;
}

AutoRocketNode AutoRocketNode::newNode(AutoRocketNode *currNode) {

  //Defining default values for a newly created node
  this->action = waitSeconds;
  this->value = 3;
  
  this->prevNode = currNode;
  this->nextNode = currNode->nextNode;
  currNode->nextNode = this;
  this->nextNode->prevNode = this;    
}

AutoRocketNode AutoRocketNode::delNode(AutoRocketNode *currNode) {
  
  this->prevNode->nextNode = this->nextNode;
  this->nextNode->prevNode = this->prevNode;

  delete this;
}

uint32_t AutoRocketNode::getAction() {
  
  return this->action;
}

uint32_t AutoRocketNode::getValue() {
  
  return this->value;
}


void AutoRocketScript::editFilename(char filename[15]) {
  
  strcpy(filename, filename);
}


void AutoRocketScript::editDescription(char description[255]) {
  
  strcpy(description, description);
}
