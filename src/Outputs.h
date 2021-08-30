#ifndef INPUTS_h
#define INPUTS_h

#include <Arduino.h>
#include "Joystick/Joystick.h"
//#include "Keyboard/Keyboard.h"
//#include "Storage/Storage.h"
//#include "Dispatcher.h"

#define TOTAL_OUTPUT_TYPES 2
#define OUTPUT_TYPE_BUTTON 0
#define OUTPUT_TYPE_AXIS 1
//#define KEYS_PER_OUTPUT 3

class Output {
  public:
    Output(uint8_t type);

    virtual void init();
    virtual void configure(uint8_t* config);
    //virtual void update(Joystick_* joystick, bool value);
    //virtual void update(Joystick_* joystick, int value);

    uint8_t id = 0;
    uint8_t pos = 0;
    uint8_t compId = 0;
    uint8_t index = 0;

    uint8_t type = 0;

    // Stores the key codes binded to the output.
    //uint8_t keys[KEYS_PER_OUTPUT] = {0};
};

class ButtonOutput: public Output {
  public:
    ButtonOutput();
    void init();
    void configure(uint8_t* config);
    void update(Joystick_* joystick, bool state);

  private:
    bool m_state = false;
};

class AxisOutput: public Output {
  public:
    AxisOutput();
    void init();
    void configure(uint8_t value);
    void update(Joystick_* joystick, uint16_t state);

  private:
    uint16_t m_state = 0;
};

#endif