/* (C)2019 Benjamin Schmid  
 *  
 *  touch.h
 *  Getting the touch coordinates
 */

#ifndef TOUCH_H
#define TOUCH_H

void initializeTouchPins();

void checkTouch();

int getTouchX();
int getTouchY();

#endif
