#ifndef OCTOPET_H
#define OCTOPET_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <UUID.h>

class OctoPet {
  private:
    bool builtinLedOn = false;

    unsigned long millisTaskDiscovery = 10001;
    unsigned long millisTaskPeriodic = 10001;

    // UUID
    UUID uuid;
    uint32_t extractEntropy();

  public:
    OctoPet();
    
    void setup();
    void loop();

    void blink();
    
    void taskDiscovery();
    void taskPeriodic();

    // UUID
    char * uuidv4();
};

#endif
