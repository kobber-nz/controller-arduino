#include "Controller.h"

Controller::Controller(char* code, uint16_t version) {
  m_code = code;
  m_version = version;
}

void Controller::begin() {
  //Keyboard.begin();
  
  // This array is used to enable/disable the different axis on the joystick.
  // It does this by setting the amount of 'true' values in the array to the
  // amount of 'axis' outputs in the components.
  bool axes[4] = {};

  for (uint8_t i = 0; i < m_outputCounter[OUTPUT_TYPE_AXIS]; i++) {
    axes[i] = true;
  }

  m_joystick = new Joystick_(
    JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
    m_outputCounter[OUTPUT_TYPE_BUTTON], 0,  // Button Count, Hat Switch Count
    false, false, axes[0],       // X, Y, Z
    axes[1], axes[2], axes[3],      // Rx, Ry, Rz
    false, false,             // Rudder, throttle
    false, false, false       // Accelerator, brake, steering
  );

  m_joystick->setZAxisRange(0, 1023);
  m_joystick->setRxAxisRange(0, 1023);
  m_joystick->setRyAxisRange(0, 1023);
  m_joystick->setRzAxisRange(0, 1023);
  m_joystick->begin();
}

void Controller::add(Component* comp) {
  // This uses 'm_compsTotal' as the value, but also increments it for the next
  // time it's used.

  comp->id = m_compsTotal;
  m_comps[m_compsTotal++] = comp;

  for(uint8_t i = 0; i < comp->inputsTotal; i++) {
    Output* output = comp->outputs[i];

    output->id = m_outputsTotal++;
    output->compId = comp->id;
    output->index = i;

    // Set the position of the output to the counter for this type.
    output->pos = m_outputCounter[output->type];

    output->init();

    // Increment the counter for this type of output.
    m_outputCounter[output->type]++;
  }
}

void Controller::update() {
  /*
  if (Serial.available() > 0) {
    uint8_t bufferSize = 0;
    uint8_t buffer[8] = {};

    while (Serial.available() > 0) {
      buffer[bufferSize++] = Serial.read();
    }

    if (buffer[0] == 1) {
      Serial.print("<controller version='"); Serial.print(m_version);
      Serial.print("' code='"); Serial.print(m_code); Serial.print("'>");

      Serial.print("<components>");
      for(uint8_t i = 0; i < m_compsTotal; i++) {
        Component* comp = m_comps[i];
        Serial.print("<component type='"); Serial.print(comp->type);
        Serial.print("'>");
        for(uint8_t i = 0; i < comp->inputsTotal; i++) {
          Output* output = comp->outputs[i];
          Serial.print("<output type='"); Serial.print(output->type);
          Serial.print("'>"); 

          for (uint8_t i = 0; i < KEYS_PER_OUTPUT; i++) {
            Serial.print("<key code='");
            Serial.print(output->keys[i]);
            Serial.print("'/>");
          }

          Serial.print("</output>");
        }
        Serial.print("</component>");
      }
      Serial.println("</components></controller>");
    } else if (buffer[0] == 2) {
      Component* comp = m_comps[buffer[1]];
      Output* output = comp->outputs[buffer[2]];

      // Offset the buffer array by 3 to reach the data.
      output->configure(buffer+3);
    } else if (buffer[0] == 3) {
      Dispatcher.configMode = buffer[1];
    }
  }
  */

  for(uint8_t i = 0; i < m_compsTotal; i++) {
    m_comps[i]->update(m_joystick);
  }
}