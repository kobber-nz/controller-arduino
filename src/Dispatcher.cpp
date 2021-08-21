#include "Dispatcher.h"

Dispatcher_ Dispatcher;

Dispatcher_::Dispatcher_() {}

void Dispatcher_::sendKeys(uint8_t* keys, uint8_t size) {
  if (configMode) return;

  for (uint8_t i = 0; i < size; i++) {
      uint8_t keyCode = keys[i];
      if (keyCode > 0) Keyboard.press(keyCode);
  }
  delay(10);
  Keyboard.releaseAll();
}