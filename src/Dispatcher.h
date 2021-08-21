#ifndef Dispatcher_h
#define Dispatcher_h

#include <Arduino.h>

#include "Keyboard/Keyboard.h"

class Dispatcher_ {
  public:
    Dispatcher_();

    void sendKeys(uint8_t* keys, uint8_t size);
    bool configMode = false;
};

extern Dispatcher_ Dispatcher;

#endif