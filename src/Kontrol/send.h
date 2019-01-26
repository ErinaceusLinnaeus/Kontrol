#ifndef SEND_H
#define SEND_H

#include <stdint.h>
#include "AutoRocket.h"

void initializeSimpit();

void updateSimpit();

void sendACG(uint32_t acg);

void sendSAS(uint32_t sas);

void sendThrottle(int16_t throttle);

void sendRotation(int16_t pitch, int16_t yaw, int16_t roll);

void sendTranslation(int16_t x, int16_t y, int16_t z);

#endif
