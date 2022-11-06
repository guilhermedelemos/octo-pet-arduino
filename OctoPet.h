#ifndef OCTOPET_H
#define OCTOPET_H

#include <Arduino.h>

class OctoPet {
  private:
    bool builtinLedOn = false;
    unsigned long millisTask1 = millis();
    unsigned long millisTask2 = millis();

  public:
    OctoPet();
    void setup();
    void loop();
    void blink();
    void task1();
    void task2();
};

#endif
