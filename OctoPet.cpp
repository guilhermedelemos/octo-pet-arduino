#include "OctoPet.h"

OctoPet::OctoPet() {
  Serial.println("OctoPet()");
}

void OctoPet::setup() {
  Serial.begin(9600);
  while (!Serial) ;
  Serial.println("OctoPet");
  Serial.println("Setup starting");

  Serial.println("Random seed");
  randomSeed(analogRead(0));

  Serial.println("UUID");
  this->uuid.seed(extractEntropy());

  Serial.println("Builtin led");
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.println("Setup finished");
  Serial.println("------------------------------");
}

void OctoPet::loop() {
  this->taskDiscovery();
  this->taskPeriodic();
}

void OctoPet::blink() {
  if(this->builtinLedOn) {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  this->builtinLedOn = !this->builtinLedOn;
}

void OctoPet::taskDiscovery() {
  if((millis() - this->millisTaskDiscovery) > 10000){
    this->millisTaskDiscovery = millis();
    DynamicJsonDocument doc(1024);
    doc["header"]["event"] = "discovery";
    doc["header"]["id"] = this->uuidv4();
    doc["sensor"] = "gps";
    doc["time"]   = 1351824120;
    doc["data"][0] = 48.756080;
    doc["data"][1] = 2.302038;
    serializeJson(doc, Serial);
    Serial.println();
  }
}

void OctoPet::taskPeriodic() {
  if((millis() - this->millisTaskPeriodic) > 1000){
    this->millisTaskPeriodic = millis();
    DynamicJsonDocument doc(1024);
    doc["header"]["event"] = "periodic";
    doc["header"]["id"] = this->uuidv4();
    doc["temperature"] = 40;
    serializeJson(doc, Serial);
    Serial.println();
  }
}

char * OctoPet::uuidv4() {
  uuid.generate();
  return uuid.toCharArray();
}

uint32_t OctoPet::extractEntropy() {
  // GET COMPILE TIME ENTROPY
  uint32_t r = 0;
  uint16_t len = strlen(__FILE__);
  for (uint16_t i = 0; i < len; i++)
  {
    r ^= __FILE__[i];
    r = r * (r << 3);
  }
  len = strlen(__DATE__);
  for (uint16_t i = 0; i < len; i++)
  {
    r ^= __DATE__[i];
    r = r * (r << 17);
  }
  len = strlen(__TIME__);
  for (uint16_t i = 0; i < len; i++)
  {
    r ^= __TIME__[i];
    r = r * (r << 7);
  }

  // GET RUNTIME ENTROPY
  //Serial.println("send 8 chars");
  uint32_t mask = 0;
  for (int i = 0; i < 8; i++) {
    mask <<= 7;
    mask ^= micros();
    delay(random(100));

    /*while (Serial.available() == 0);
    if (Serial.available())
    {
      mask <<= 7;
      mask ^= micros();
      Serial.read();
    }*/
  }
  return r ^ mask;
}
