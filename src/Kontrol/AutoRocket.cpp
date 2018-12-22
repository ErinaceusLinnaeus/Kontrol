/* (C)2018 Benjamin Schmid  
 *  
 *  AutoRocket.cpp
 */

#include "AutoRocket.h"
#include <string.h>

AutoRocketScript::AutoRocketScript() {

  this->setFilename("newScript");
  this->setDescription("Describe me...");

  this->firstNode = new AutoRocketNode();
  this->lastNode = new AutoRocketNode(theExitNode, 0);
  
//This needed the nodes to be public
//  this->firstNode->prevNode = NULL;
//  this->firstNode->nextNode = this->lastNode;
//This is with private nodes
  this->firstNode->setPrevNode(this->firstNode, NULL);
  this->firstNode->setNextNode(this->firstNode, this->lastNode);
  
//This needed the nodes to be public
//  this->lastNode->prevNode = this->firstNode;
//  this->lastNode->nextNode = NULL;
//This is with private nodes
  this->lastNode->setPrevNode(this->lastNode, this->firstNode);
  this->lastNode->setNextNode(this->lastNode, NULL);

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
  this->action = waitTenthSeconds;
  this->value = 30;
}

//Constructing a Node
AutoRocketNode::AutoRocketNode(todos action, uint32_t value) {

  this->action = action;
  this->value = value;
}

AutoRocketNode AutoRocketNode::newNode(AutoRocketNode *currNode) {

  AutoRocketNode* temp;
  temp = new AutoRocketNode();
  
  temp->prevNode = currNode;
  temp->nextNode = currNode->nextNode;
  currNode->nextNode = temp;
  temp->nextNode->prevNode = temp;

  return *temp;
}

void AutoRocketNode::delNode(AutoRocketNode *node) {
  
  node->prevNode->nextNode = node->nextNode;
  node->nextNode->prevNode = node->prevNode;

  delete node;
}

uint32_t AutoRocketNode::getAction() {
  
  return this->action;
}

uint32_t AutoRocketNode::getValue() {
  
  return this->value;
}

void AutoRocketNode::setPrevNode(AutoRocketNode* currNode, AutoRocketNode* prevNode){

  currNode->prevNode = prevNode;
}

void AutoRocketNode::setNextNode(AutoRocketNode* currNode, AutoRocketNode* nextNode){
  
  currNode->nextNode = nextNode;
}



AutoRocketNode AutoRocketScript::getCurrentNode(){

  return *currNode;
}

char AutoRocketScript::getFilename(){

  return filename[15];
}

char AutoRocketScript::getDescription(){
  
  return description[255];
}

void AutoRocketScript::setFilename(char filename[15]) {
  
  strcpy(filename, filename);
  saveScript();
}


void AutoRocketScript::setDescription(char description[255]) {
  
  strcpy(description, description);
  saveScript();
}
