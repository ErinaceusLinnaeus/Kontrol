/*  (C)2018 Benjamin Schmid
 *   
 *  AutoRocketScript.h
 *  Definition of classes to create a doubly linked list to perform auto piloting
 */

#ifndef AUTOROCKETSCRIPT_H
#define AUTOROCKETSCRIPT_H

#include <stdint.h>

/*
 * Types of things a node can do:
 * Wait some time.
 * Wait until a distance to a target is reached.
 * Wait until a given radar altitude.
 * Wait until a given altitude in meter.
 * Wait until a given altitude in kilometer.
 * Change the throttle.
 * Stage.
 * Toggle an action group.
 * Change the attitude.
 * Change the translation.
 * Exit, being the last node.
 */
enum todos {waitSeconds, waitForDistanceCM, waitForRAltM, waitForAltM, waitForAltKM, setThrottle, setStage, toggleACG, setAttitude, setTranslation, Exit};

/*A class to program for autofly mode
 * First a name you can enter
 * And a description you can enter
 * Let the rocket do something or exit:
 *  Value is either... (max. 4.294.967.295)
 *    ...the time to wait[seconds]
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
 *    attitude
 *      00000xxx xxxxxxyy yyyyyyyz zzzzzzzz                    ->  360° (z) + 360°*512 (y) + 360°*262.144 (x)
 *      x, y, z in planetary reference frame
 *    translation
 *      00000xxx xxxxxxyy yyyyyyyz zzzzzzzz                    ->  360° (z) + 360°*512 (y) + 360°*262.144 (x)
 *      x, y, z in planetary reference frame
 *    exit (exit point at last node)
 *      00000000 00000000 00000000 00000000
 */
class AutoRocketNode {
  private:
    todos action;
    uint32_t value;
    AutoRocketNode *prevNode;
    AutoRocketNode *nextNode;

  public:
    void newNode();
    void editNode(todos a, uint32_t v);
    void deleteNode();
    uint32_t getAction();
    uint32_t getValue();
    AutoRocketNode getPrevNode();
    AutoRocketNode getNextNode();
};

class AutoRocketScript {

  private:
    char filename[15], description[255];
    AutoRocketNode *firstNode;
    AutoRocketNode *lastNode;
    void saveScript();

  public:
    void newScript(char filename[15], char description[255]);
    void loadScript(char filename[15]);
    void editFilename(char filename[15]);
    void editDescription(char description[255]);
    void deleteScript();
    char getFilename();
    char getDescription();
    AutoRocketNode getFirstNode();
};

#endif
