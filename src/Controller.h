#ifndef Controller_h
#define Controller_h

#include <Arduino.h>

// The joystick library (https://github.com/MHeironimus/ArduinoJoystickLibrary)
// is used to emulate a game controller on the connected pc.
#include "Joystick/Joystick.h"

// The keyboard library (https://github.com/arduino-libraries/Keyboard)
// is used to emulate key presses on the connected pc.
//#include "Keyboard/Keyboard.h"

#include "Components.h"
//#include "Dispatcher.h"

/** 
 * The primary class that handles all emulation and communication to the
 * computer.
*/
class Controller {
  public:
    Controller(char* code, uint16_t version);
    
    void begin();
    void add(Component* comp);
    void update();

  private:
    Joystick_* m_joystick;

    /**
     * Stores all component instances.
    */
    Component* m_comps[18];

    /** 
     * Stores the total amount of components in the 'comps' array.
    */
    uint8_t m_compsTotal = 0; 

    uint8_t m_outputsTotal = 0; 

    /**
     * For counting the total number of different output types. Used to assign
     * positions to component outputs.
    */
    uint8_t m_outputCounter[TOTAL_OUTPUT_TYPES] = {0};

    /**
     * Stores the design code for the controller. This code is used in the 
     * configurator software to display the design.
    */
    char* m_code;

    uint16_t m_version;
};

#endif