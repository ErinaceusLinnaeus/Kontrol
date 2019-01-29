/* (C)2019 Benjamin Schmid  
 *  
 *  communication.h
 *  Here we communicate withthe KSP Simpit plugin
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include "AutoRocket.h"

void initializeSimpit();

void updateSimpit();

int checkAbortFlag();
void unsetAbortFlag();

void sendCommand(uint32_t command, uint32_t value);
void sendThrottle(int16_t throttle);
void sendRotation(int16_t pitch, int16_t yaw, int16_t roll);
void sendTranslation(int16_t x, int16_t y, int16_t z);

char* checkCommand(uint32_t command, uint32_t value);

#endif
