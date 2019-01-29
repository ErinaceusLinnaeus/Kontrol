/*  (C)2019 Benjamin Schmid
 *   
 *  AutoRocket.h
 *  Definition of classes to create a doubly linked list to perform auto piloting
 */

#ifndef AUTOROCKET_H
#define AUTOROCKET_H

#include <stdint.h>

/*A class to program for autofly mode
 * First a name you can enter
 * And a description you can enter
 * Let the rocket do something or exit:
 *  Command             |   Value
 *    NIX               |   any
 *    acg1              |   0:deactivate, 1:toggle, 2:activate
 *    acg2              |   0:deactivate, 1:toggle, 2:activate
 *    acg3              |   0:deactivate, 1:toggle, 2:activate
 *    acg4              |   0:deactivate, 1:toggle, 2:activate
 *    acg5              |   0:deactivate, 1:toggle, 2:activate
 *    acg6              |   0:deactivate, 1:toggle, 2:activate
 *    acg7              |   0:deactivate, 1:toggle, 2:activate
 *    acg8              |   0:deactivate, 1:toggle, 2:activate
 *    acg9              |   0:deactivate, 1:toggle, 2:activate
 *    acg10             |   0:deactivate, 1:toggle, 2:activate
 *    acgStage          |   any
 *    acgAbort          |   any, 0 will ignore safety
 *    acgLight          |   0:deactivate, 1:toggle, 2:activate
 *    acgGear           |   0:deactivate, 1:toggle, 2:activate
 *    acgBrakes         |   0:deactivate, 1:toggle, 2:activate
 *    acgRCS            |   0:deactivate, 1:toggle, 2:activate
 *    acgSAS            |   0:deactivate, 1:toggle, 2:activate
 *    sasStability      |   any, activates SAS
 *    sasManeuver       |   any, activates SAS
 *    sasPrograde       |   any, activates SAS
 *    sasRetrograde     |   any, activates SAS
 *    sasNormal         |   any, activates SAS
 *    sasAntinormal     |   any, activates SAS
 *    sasRadialin       |   any, activates SAS
 *    sasRadialout      |   any, activates SAS
 *    sasTarget         |   any, activates SAS
 *    sasAntitarget     |   any, activates SAS
 *    setThrottle       |   0...100
 *    waitForDistanceCM |   0...4.294.967.295
 *    waitForDistanceCM |   0...4.294.967.295
 *    waitForRAltM      |   0...4.294.967.295
 *    waitForAltM       |   0...4.294.967.295
 *    waitForAltKM      |   0...4.294.967.295
 *    theExitNode       |   any
 *    
 *    auroli.setFilename("Go Rocket, go.");
 *    auroli.setDescription("Just playing around...");
 *    auroli.newNode(command, value, "info");
 *    auroli.delNode();
 *    auroli.goToTheTop();
 */

enum command {NIX, acg1, acg2, acg3, acg4, acg5, acg6, acg7, acg8, acg9, acg10, acgStage, acgAbort, acgLight, acgGear, acgBrakes, acgRCS, acgSAS, sasStability, sasManeuver, sasPrograde, sasRetrograde, sasNormal, sasAntinormal, sasRadialin, sasRadialout, sasTarget, sasAntitarget, setThrottle, waitTenthSeconds, waitForDistanceCM, waitForRAltM, waitForAltM, waitForAltKM, theExitNode};

class AutoRocketNode {
  
  private:
    //The Data
    command action;
    uint32_t value;
    char information[31];

  public:
    //The Nodes
    AutoRocketNode* prevNode;
    AutoRocketNode* nextNode;
    
    //Constructors
    AutoRocketNode();
    AutoRocketNode(command action, uint32_t value, char information[31]);

    //Getting Data
    command getAction();
    uint32_t getValue();
    char* getInformation();

    //Manipulating Data
    void setAction(AutoRocketNode *node, command action);
    void setValue(AutoRocketNode *node, uint32_t value);
    void setInformation(AutoRocketNode *node, char information[31]);
};

class AutoRocketList {

  private:
    //The Data
    char filename[31], description[255];
    
    //The Nodes
    AutoRocketNode* firstNode;
    AutoRocketNode* lastNode;
    AutoRocketNode* currNode;

  public:
    //Constructor
    AutoRocketList();

    //Getting Data
    char* getFilename();
    char* getDescription();
    AutoRocketNode* getFirstNode();
    AutoRocketNode* getLastNode();
    AutoRocketNode* getCurrNode();
    
    //Manipulating Data
    void saveScript();
    void setFilename(char filename[31]);
    void setDescription(char description[255]);

    //Manage Nodes
    void newNode(command action, uint32_t value, char information[255]);
    void delNode();

    //Navigating the nodes
    void goToPrevNode();
    void goToNextNode();
    void goToTheTop();

    //Activate the auto pilot
    void launchList();
};

#endif
