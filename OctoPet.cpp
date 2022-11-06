#include "OctoPet.h"

OctoPet::OctoPet() {
  Serial.println("OctoPet()");
}

void OctoPet::setup() {
  Serial.begin(9600);
  // wait for serial port to connect. Needed for native USB port only
  while (!Serial) {
    ;
  }
  Serial.println("OctoPet");
  Serial.println("Setup starting");

  Serial.println("Builtin led");
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.println("Setup finished");
  Serial.println("------------------------------");
}

void OctoPet::loop() {
  this->task1();
  this->task2();
}

void OctoPet::blink() {
  if(this->builtinLedOn) {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  this->builtinLedOn = !this->builtinLedOn;
}

void OctoPet::task1() {
  if((millis() - this->millisTask1) > 200){
    this->millisTask1 = millis();
    Serial.println("task1()");
    this->blink();
  }
}

void OctoPet::task2() {
  if((millis() - this->millisTask2) > 5000){
    this->millisTask2 = millis();
    Serial.println("task2()");
  }
}
