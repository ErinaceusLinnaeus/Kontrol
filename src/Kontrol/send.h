#ifndef SEND_H
#define SEND_H

#include <stdint.h>
#include "AutoRocket.h"

void initializeSimpit();

void updateSimpit();

void sendACG(uint32_t acg);

void sendSAS(uint32_t sas);

void sendThrottle(uint32_t throttle);

#endif
