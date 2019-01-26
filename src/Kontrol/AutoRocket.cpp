/* (C)2018 Benjamin Schmid  
 *  
 *  AutoRocket.cpp
 */

#include "AutoRocket.h"
#include <string.h>
//to use sprintf - convert integer to char*
#include <stdio.h>
#include "send.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


char* getTodosString(todos action){
  
  switch(action){
      case waitTenthSeconds:
       return "waitTenthSeconds";
      case waitForDistanceCM:
       return "waitForDistanceCM";
      case waitForRAltM:
       return "waitForRAltM";
      case waitForAltM:
       return "waitForAltM";
      case waitForAltKM:
       return "waitForAltKM";
      case setThrottle:
       return "setThrottle";
      case toggleACG:
       return "toggleACG";
      case setSAS:
       return "setSAS";
      case theExitNode:
       return "theExitNode";
      default:
       return "outOfRange";
    }
}

void AutoRocketList::launchList() {

  AutoRocketNode* currNode = this->firstNode;

  while(currNode != NULL) {

    int currAction = currNode->getAction();
    int currValue = currNode->getValue();

    if (currAction == waitTenthSeconds)
      //Wait some time
      delay(currValue * 100);
    else if (currAction == waitForDistanceCM)
      //Wait for a distance [cm]
      NULL;
    else if (currAction == waitForRAltM)
      //Wait for radar altitude [m]
      NULL;
    else if (currAction == waitForAltM)
      //Wait for altitude [m]
      NULL;
    else if (currAction == waitForAltKM)
      //Wait for altitude [km]
      NULL;
    else if (currAction == setThrottle)
      //Set throttle
      sendThrottle(currValue);
    else if (currAction == toggleACG)
      //Toggle an action group
      sendACG(currValue);
      //Set SAS Mode
      sendSAS(currValue);
    
    currNode = currNode->nextNode;
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

}


//Default Constructor creates a 3sec waiting node
AutoRocketNode::AutoRocketNode() {

  //Defining default values for the first node
  this->action = waitTenthSeconds;
  this->value = 30;
  strcpy(this->information, "Wait for 3 sec...");
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

void AutoRocketList::setFilename(char filename[31]) {
  
  strcpy(this->filename, filename);
//  saveScript();
}


void AutoRocketList::setDescription(char description[255]) {
  
  strcpy(this->description, description);
//  saveScript();
}


void AutoRocketList::goToNextNode(){

  //Don't try to jump over theExitNode
  if (this->currNode->nextNode != NULL)
    this->currNode = this->currNode->nextNode;
   else
    //We reached the end of the list
    NULL;
}


void AutoRocketList::goToPrevNode(){

  this->currNode = this->currNode->prevNode;
}

void AutoRocketList::goToTheTop(){

  this->currNode = this->firstNode;
}
