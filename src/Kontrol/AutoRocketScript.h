/*  (C)2018 Benjamin Schmid
 *   
 *  AutoRocketScript.h
 *  Definition of classes to create a doubly linked list to perform auto piloting
 */

#ifndef AUTOROCKETSCRIPT_H
#define AUTOROCKETSCRIPT_H

#include <stdint.h>

/*A class to program for autofly mode
 * First a name you can enter
 * And a description you can enter
 * Let the rocket do something or exit:
 *  Command is either... (max. 268.435.456) *  
 *    ...the time to wait[seconds] - max. 4.473.924 min 16 s
 *                                   186.413 h 30 min 39 s
 *                                   7.767 d 5 h 30 min 39 s
 *                                   ~ 28 y
 *      0001 xxxx xxxxxxxx xxxxxxxx xxxxxxxx
 *    ...the distance (to a target) [centimeter]
 *      0010 xxxx xxxxxxxx xxxxxxxx xxxxxxxx
 *    ...the (radar)altitude [meter]
 *      0011 xxxx xxxxxxxx xxxxxxxx xxxxxxxx
 *    ...the altitude [meter]
 *      0100 xxxx xxxxxxxx xxxxxxxx xxxxxxxx
 *    ...the altitude [kilometer] - ca. 1,8 au
 *      0101 xxxx xxxxxxxx xxxxxxxx xxxxxxxx
 *    ...throttle [%]
 *      0110 0000 00000000 00000000 0xxxxxxx
 *    stage
 *      0111 1111 11111111 11111111 11111111
 *    actiongroup, also SAS, RCS, Brakes, Gear, etc.
 *      1000 0000 00000000 00000000 0xxxxxxx - AG off
 *      1001 0000 00000000 00000000 1xxxxxxx - AG on
 *    attitude
 *      1010 0000 xxxxxxxx yyyyyyyy zzzzzzzz
 *      x, y, z in planetary reference frame
 *    translate
 *      1011 0000 xxxxxxxx yyyyyyyy zzzzzzzz
 *      x: roll
 *      y: pitch
 *      z: yaw
 *    exit (exit point at last node)
 *      1111 0000 00000000 00000000 00000000
 */
class AutoRocketNode {
  private:
    uint32_t command;
    char message[127];
    AutoRocketNode *prevNode;
    AutoRocketNode *nextNode;

  public:
    void newNode();
    void editCommand(uint32_t command);
    void editMessage(char message[127]);
    void unloadNode();
    uint32_t getCommand();
    char getMessage();
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
    void unloadScript();
    void deleteScript();
    char getFilename();
    char getDescription();
    AutoRocketNode getFirstNode();
};

#endif
