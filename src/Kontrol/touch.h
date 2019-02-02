/*  (C)2019 Benjamin Schmid
 *   
 *  touch.h
 *  Simplifying touch screen coordinates
 */
 
#ifndef TOUCH_H
#define TOUCH_H

#include <arduino.h>
#include <TouchScreen.h>

class TouchPanel {

  private:
    //Pins connected to the touchscreen
    const int YP = A10;
    const int XM = A11;
    const int YM = 14;
    const int XP = 15;
    
    //A 3 dimensional point...
    TSPoint p;
    //...and the panel. For better pressure precision: I messured 540 Ohm between XP and XM
    TouchScreen ts = TouchScreen(XP, YP, XM, YM, 540);

    public:
      //Debug function
      void check();
      
      //Panel divided into larger field areas
      int getStoreyX();
      int getStoreyY();

      //Basically a boolean
      int getTouchZ();

      //Precise position
      int getPreciseX();
      int getPreciseY();
      int getPreciseZ();
};

#endif
