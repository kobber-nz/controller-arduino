#include <Arduino.h>
#include "src/Controller.h"

Controller controller("DEV-2", 2);

void setup() {
  controller.add( new Switch(5,6, NORMAL) );
  controller.add( new Button(4) );

  controller.begin();
}

void loop() {
  controller.update();
  delay(20);
}
