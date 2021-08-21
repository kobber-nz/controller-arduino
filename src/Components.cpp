#include "Components.h"

Component::Component(uint8_t type) {
  this->type = type;
}

void Component::add(Output* output) {
  outputs[inputsTotal++] = output;
}

/* -------- BUTTON ---------------------------------------------------------- */
Button::Button(uint8_t pin): Component(COMPONENT_TYPE_BUTTON) {
  // This expression passes the new output to the 'add' function, while also
  // the value of a variable to it. This works because the '=' expression
  // returns the new value of the variable after setting it.
  add(m_output = new ButtonOutput());

  pinMode(pin, INPUT_PULLUP);
  m_pin = pin;
}
void Button::update(Joystick_* joystick) {
  // Invert the reading because its LOW when grounded (pulled up).
  bool state = !digitalRead(m_pin);

  m_output->update(joystick, state);
}
/* -------------------------------------------------------------------------- */

/* -------- SWITCH ---------------------------------------------------------- */
Switch::Switch(uint8_t pinOne, bool inverted): Component(COMPONENT_TYPE_SWITCH) {
  // The switch requires two button outputs (one for each position).
  add(m_outputOne = new ButtonOutput());
  add(m_outputTwo = new ButtonOutput());

  pinMode(pinOne, INPUT_PULLUP);
  m_inverted = inverted;
  m_pinOne = pinOne;
}
Switch::Switch(uint8_t pinOne, uint8_t pinTwo, bool inverted): Component(COMPONENT_TYPE_SWITCH) {
  add(m_outputOne = new ButtonOutput());
  add(m_outputTwo = new ButtonOutput());
  add(m_outputThree = new ButtonOutput());

  pinMode(pinOne, INPUT_PULLUP);
  pinMode(pinTwo, INPUT_PULLUP);

  m_pinOne = pinOne;
  m_pinTwo = pinTwo;
}
void Switch::update(Joystick_* joystick) {
  bool stateOne = !digitalRead(m_pinOne);

  if (m_inverted) stateOne = !stateOne;

  if (inputsTotal == 1) {
    // The state of the second output should be the opposite of the first output.
    m_outputOne->update(joystick, stateOne);
    //m_outputTwo->update(joystick, !stateOne);
  } else {
    bool stateTwo = !digitalRead(m_pinTwo);

    m_outputOne->update(joystick, stateOne);
    m_outputThree->update(joystick, stateTwo);

    // Activate the second output (middle position) if both of the other pins
    // are not active.
    //m_outputTwo->update(joystick, !stateOne && !stateTwo); // REMOVED
  }
}
/* -------------------------------------------------------------------------- */

/* -------- POTENTIOMETER --------------------------------------------------- */
Potentiometer::Potentiometer(uint8_t pin, bool inverted): Component(COMPONENT_TYPE_POTENTIOMETER) {
  add(m_output = new AxisOutput());

  pinMode(pin, INPUT);
  m_inverted = inverted;
  m_pin = pin;
}
void Potentiometer::update(Joystick_* joystick) {
  uint16_t value = analogRead(m_pin);

  if (m_inverted) value = 1023-value;

  m_output->update(joystick, value);
}
/* -------------------------------------------------------------------------- */