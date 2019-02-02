/*  (C)2018 Benjamin Schmid
 *   
 *  DisplayOperations.h
 *  Definition of functions to print things on the TFT Display through the HDMI port
 */

#ifndef DISPLAYOPERATIONS_H
#define DISPLAYOPERATIONS_H

//#include <TFT_HX8357_Due.h>
//Part of the All_Free_Fonts_Demo of the TFT library
#include "Free_Fonts.h"

class Display {

  public:
    //The actual display
//    TFT_HX8357_Due tft = TFT_HX8357_Due();
    void initialize();

    void printBlack();
    void printInt(int i);
};

#endif
