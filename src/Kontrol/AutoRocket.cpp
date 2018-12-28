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
  this->lastNode = new AutoRocketNode(theExitNode, 0, "EXIT");
  
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
  strcpy(this->information, "Waiting...");
}

//Constructing a Node
AutoRocketNode::AutoRocketNode(todos action, uint32_t value, char information[31]) {

  this->action = action;
  this->value = value;
  strcpy(this->information, information);
}

void AutoRocketList::newNode(todos action, uint32_t value, char information[31]) {

  AutoRocketNode* temp;
  temp = new AutoRocketNode();

  temp->setAction(temp, action);
  temp->setValue(temp, value);
  temp->setInformation(temp, information);
//  temp->action = action;
//  temp->value = value;
  
  temp->prevNode = currNode;
  temp->nextNode = currNode->nextNode;
  this->currNode->nextNode = temp;
  temp->nextNode->prevNode = temp;

  this->goToNextNode();
}

void AutoRocketList::delNode() {

  AutoRocketNode* temp;
  temp = this->currNode;
  this->currNode->prevNode->nextNode = this->currNode->nextNode;
  this->currNode->nextNode->prevNode = this->currNode->prevNode;
  this->goToPrevNode();

  delete temp;
  
}


void AutoRocketNode::setAction(AutoRocketNode *node, todos action){

  this->action = action;
}


void AutoRocketNode::setValue(AutoRocketNode *node, uint32_t value){

  this->value = value;
}


void AutoRocketNode::setInformation(AutoRocketNode *node, char information[31]) {
  
  strcpy(this->information, information);
//  saveScript();
}


todos AutoRocketNode::getAction() {
  
  return this->action;
}

uint32_t AutoRocketNode::getValue() {
  
  return this->value;
}

char* AutoRocketNode::getInformation(){

  return this->information;
}

char* AutoRocketList::getFilename(){

  return this->filename;
}

char* AutoRocketList::getDescription(){
  
  return this->description;
}

AutoRocketNode* AutoRocketList::getFirstNode(){
  
  return this->firstNode;
}

AutoRocketNode* AutoRocketList::getLastNode(){
  
  return this->lastNode;
}

AutoRocketNode* AutoRocketList::getCurrNode(){
  
  return this->currNode;
}

void AutoRocketList::setFilename(char filename[15]) {
  
  strcpy(this->filename, filename);
//  saveScript();
}


void AutoRocketList::setDescription(char description[255]) {
  
  strcpy(this->description, description);
//  saveScript();
}


void AutoRocketList::goToNextNode(){

  this->currNode = this->currNode->nextNode;
}


void AutoRocketList::goToPrevNode(){

  this->currNode = this->currNode->prevNode;
}

void AutoRocketList::goToTheTop(){

  this->currNode = this->firstNode;
}
