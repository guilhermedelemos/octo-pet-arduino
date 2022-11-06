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
    doc[F("header")][F("eventType")] = F("discovery");
    doc[F("header")][F("eventId")] = this->uuidv4();
    doc[F("header")][F("triggerTime")] = "2022-01-01T00:00:00.0";
    doc[F("device")][F("id")] = "abc123";
    doc[F("device")][F("softwareVersion")] = "1.0.0";    
    doc[F("device")][F("hardwareVersion")] = "1.0.0";
    /*doc[F("device")][F("secondaryMemory")]["cardType"] = "1.0.0";
    doc[F("device")][F("secondaryMemory")]["clusters"] = "1.0.0";
    doc[F("device")][F("secondaryMemory")]["blocksPerCluster"] = "1.0.0";
    doc[F("device")][F("secondaryMemory")]["totalBlocks"] = "1.0.0";
    doc[F("device")][F("secondaryMemory")][F("volumeType")] = "1.0.0";
    doc[F("device")][F("secondaryMemory")]["volumeSize"] = "1.0.0";*/
    doc[F("rollCallData")][0][F("id")] = "pow234";
    doc[F("rollCallData")][0][F("sensor")] = "DHT22";
    doc[F("rollCallData")][0][F("address")] = "D2";
    doc[F("rollCallData")][0][F("category")] = "room";
    doc[F("rollCallData")][1][F("id")] = "03392";
    doc[F("rollCallData")][1][F("sensor")] = "PH0";
    doc[F("rollCallData")][1][F("address")] = "A1";
    doc[F("rollCallData")][1][F("category")] = "water";
    serializeJson(doc, Serial);
    Serial.println();
  }
}

void OctoPet::taskPeriodic() {
  if((millis() - this->millisTaskPeriodic) > 1000){
    this->millisTaskPeriodic = millis();
    DynamicJsonDocument doc(1024);
    doc[F("header")][F("eventType")] = F("periodic");
    doc[F("header")][F("eventId")] = this->uuidv4();
    doc[F("header")][F("triggerTime")] = "2022-01-01T00:00:00.0";
    doc[F("device")][F("id")] = "abc123";
    doc[F("device")][F("softwareVersion")] = "1.0.0";    
    doc[F("device")][F("hardwareVersion")] = "1.0.0";
    doc[F("device")][F("secondaryMemory")][F("type")] = "SD2";
    doc[F("device")][F("secondaryMemory")][F("volumeType")] = "FAT32";
    doc[F("device")][F("secondaryMemory")][F("size")] = 1024;
    doc[F("deviceSample")][F("freeMemory")] = 1;
    doc[F("deviceSample")][F("batteryPowered")] = false;
    doc[F("roomSample")][F("temperature")] = 40;
    doc[F("roomSample")][F("relativeHumidity")] = 80;
    doc[F("roomSample")][F("atmosphericPressure")] = 10;
    doc[F("roomSample")][F("altitude")] = 410;
    doc[F("waterSample")][F("temperature")] = 25;
    doc[F("waterSample")][F("totalDissolvedSolids")] = 25;
    doc[F("waterSample")][F("waterLevel")] = "high";
    serializeJson(doc, Serial); // https://arduinojson.org/v6/api/json/serializejson/
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
