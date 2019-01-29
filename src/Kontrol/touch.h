/*  (C)2019 Benjamin Schmid
 *   
 *  touch.h
 *  Simplifying touch screen coordinates
 */
 
#ifndef TOUCH_H
#define TOUCH_H

void checkTouch();

int getStoreyX();
int getStoreyY();

int getTouchZ();

int getPreciseX();
int getPreciseY();

#endif
