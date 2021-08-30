#ifndef COMPONENTS_h
#define COMPONENTS_h

#include <Arduino.h>
#include "Outputs.h"

#define NORMAL false
#define INVERTED true

#define COMPONENT_TYPE_BUTTON 0
#define COMPONENT_TYPE_SWITCH 1
#define COMPONENT_TYPE_POTENTIOMETER 2
/**
 * The base class that is extended by all components. Only handles adding
 * outputs.
*/
class Component {
  public:
    Component(uint8_t type);
    virtual void update(Joystick_* joystick);

    void add(Output* output);
    
    uint8_t id = 0;
    uint8_t type = 0;
    Output* outputs[3];
    uint8_t inputsTotal = 0;
};

/**
 * The most basic component. Activates a button output when the given pin is LOW.
*/
class Button: public Component {
  public:
    /**
     * @param pin A pin that is grounded to activate this component.
    */
    Button(uint8_t pin);
    void update(Joystick_* joystick);
    
  private:
    ButtonOutput* m_output;
    uint8_t m_pin;
};

/**
 * Represents two-way and three-way switches. 
 * 
 * If one pin is given, the first output will be activated on LOW, and the second 
 * output will be activated on HIGH. This is so the top and bottom positions can 
 * be configured separately.
 * 
 * If two pins are given, the first output will be activated when the first pin
 * is LOW, and the third output will be activated when the second pin is LOW.
 * The second output will only be activated when both outputs are HIGH, so
 * something can be configured for the middle position.
*/
class Switch: public Component {
  public:
    /**
     * @param pinOne A pin that represents one position of the switch.
    */
    Switch(uint8_t pinOne, bool inverted = false);

    /**
     * @param pinOne A pin that represents the top position of the switch.
     * @param pinTwo A pin that represents the bottom position of the switch.
    */
    Switch(uint8_t pinOne, uint8_t pinTwo, bool inverted);
    void update(Joystick_* joystick);
    
  private:
    ButtonOutput* m_outputOne;
    ButtonOutput* m_outputTwo;
    //ButtonOutput* m_outputThree;

    uint8_t m_pinOne;
    uint8_t m_pinTwo;

    bool m_inverted = false;
};

/**
 * Reads the value of an analog pin and uses it to set the value of an axis
 * on the controller.
*/
class Potentiometer: public Component {
  public:
    /**
     * @param pin An analog pin to read from.
     * @param inverted If true, the value from the pin will be inverted.
    */
    Potentiometer(uint8_t pin, bool inverted = false);
    void update(Joystick_* joystick);
    
  private:
    AxisOutput* m_output;
    bool m_inverted = false;
    uint8_t m_pin;
};

#endif