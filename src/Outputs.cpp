#include "Outputs.h"

Output::Output(uint8_t type) {
  this->type = type;
}

ButtonOutput::ButtonOutput(): Output(OUTPUT_TYPE_BUTTON) {}
void ButtonOutput::init() {
  // Load each key code from the EEPROM
  /*
  for (uint8_t i = 0; i < KEYS_PER_OUTPUT; i++) {
    uint8_t data = EEPROM.read( (id*KEYS_PER_OUTPUT)+i );

    // Uninitialized EEPROM data is 255, so we should ignore it.
    if (data != 255) keys[i] = data;
  }
  */
}
/*void ButtonOutput::configure(uint8_t* config) {
  
  for (uint8_t i = 0; i < KEYS_PER_OUTPUT; i++) {
    if (keys[i] != config[i]) {
      keys[i] = config[i];

      // Save the key code to EEPROM
      EEPROM.write((id*KEYS_PER_OUTPUT)+i, config[i]);
    }
  }
  
}*/
void ButtonOutput::update(Joystick_* joystick, bool state) {
  if (m_state == state) return;

  if (state) {
    joystick->pressButton(pos);
    delay(5);

    /*
    for (uint8_t i = 0; i < KEYS_PER_OUTPUT; i++) {
      uint8_t keyCode = keys[i];
      if (keyCode > 0) Keyboard.press(keyCode);
    }

    delay(10);

    Keyboard.releaseAll();
    */

    //Dispatcher.sendKeys(keys, KEYS_PER_OUTPUT);
  } else {
    joystick->releaseButton(pos);
    delay(5);
  }

  /*
  if (Dispatcher.configMode) {
    uint8_t data[3] = {compId, index, state};
    Serial.write(data, 3);
  }
  */

  m_state = state;
}

AxisOutput::AxisOutput(): Output(OUTPUT_TYPE_AXIS) {}
void AxisOutput::init() {}
//void AxisOutput::configure(uint8_t value) {}
void AxisOutput::update(Joystick_* joystick, uint16_t state) {
  if (m_state == state) return;

  switch(pos) {
    case 0:
      joystick->setZAxis(state);
      break;
    case 1:
      joystick->setRxAxis(state);
      break;
    case 2:
      joystick->setRyAxis(state);
      break;
    case 3:
      joystick->setRzAxis(state);
      break;
  }
  
  m_state = state;
}