#ifndef JOYSTICKS_H
#define JOYSTICKS_H

void initializeJoystickPins();

void checkJoysticks();

int getSASpitch();
int getSASyaw();
int getSASroll();

int getRCSx();
int getRCSy();
int getRCSz();

#endif
