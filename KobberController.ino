#include <Arduino.h>
#include "src/Controller.h"

Controller controller("DEV-2", 2);

void setup() {
  Serial.begin(9600);

  controller.add( new Button(5) );
  controller.add( new Button(6) );

  controller.begin();
}

void loop() {
  controller.update();
  delay(50);
}
