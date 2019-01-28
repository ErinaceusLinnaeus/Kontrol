/*  (C)2019 Benjamin Schmid
 *   
 *  AutoRocket.h
 *  Definition of classes to create a doubly linked list to perform auto piloting
 */

#ifndef AUTOROCKET_H
#define AUTOROCKET_H

#include <stdint.h>

/*
 * Types of things a node can do:
 * Wait some time.
 * Wait until a distance to a target in centimeter is reached.
 * Wait until a given radar altitude in meter.
 * Wait until a given altitude in meter.
 * Wait until a given altitude in kilometer.
 * Change the throttle.
 * Stage.
 * Toggle an action group.
 * Change the attitude.
 * Change the translation.
 * Exit, being the last node.
 */
/*A class to program for autofly mode
 * First a name you can enter
 * And a description you can enter
 * Let the rocket do something or exit:
 *  Value is either... (max. 4.294.967.295)
 *    ...the time to wait[tenth-of-a-seconds] - 4971 d - 06:28:15 ~> 13 years 6 months
 *      xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx
 *    ...the distance (to a target) [centimeter]
 *      xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx
 *    ...the (radar)altitude [meter]
 *      xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx
 *    ...the altitude [meter]
 *      xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx
 *    ...the altitude [kilometer]
 *      xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx
 *    ...throttle [%]
 *      00000000 00000000 00000000 0xxxxxxx
 *    stage
 *      11111111 11111111 11111111 11111111
 *    actiongroup, also SAS, RCS, Brakes, Gear, etc.
 *      00000000 00000000 00000000 0xxxxxxx
 *    exit (exit point at last node)
 *      00000000 00000000 00000000 00000000
 */
 
enum todos {waitTenthSeconds, waitForDistanceCM, waitForRAltM, waitForAltM, waitForAltKM, setThrottle, toggleACG, setSAS, theExitNode};

enum acgIdentifier {acgStage, acg1, acg2, acg3, acg4, acg5, acg6, acg7, acg8, acg9, acg10, acgAbort, acgLight, acgGear, acgBrakes, acgRCS, acgSAS};

enum sasMode {sasStability, sasManeuver, sasPrograde, sasRetrograde, sasNormal, sasAntinormal, sasRadialin, sasRadialout, sasTarget, sasAntitarget};

char* getTodosString(todos action);

class AutoRocketNode {
  
  private:
    //The Data
    todos action;
    uint32_t value;
    char information[31];

  public:
    //The Nodes
    AutoRocketNode* prevNode;
    AutoRocketNode* nextNode;
    
    //Constructors
    AutoRocketNode();
    AutoRocketNode(todos action, uint32_t value, char information[31]);

    //Getting Data
    todos getAction();
    uint32_t getValue();
    char* getInformation();

    //Manipulating Data
    void setAction(AutoRocketNode *node, todos action);
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
    void newNode(todos action, uint32_t value, char information[255]);
    void delNode();

    //Navigating the nodes
    void goToPrevNode();
    void goToNextNode();
    void goToTheTop();

    //Activate the auto pilot
    void launchList();
};

#endif
