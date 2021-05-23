#include <Arduino.h>
#include <Wire.h>

#include "constants.h"
#include "hexapodmanager.h"
#include "servo_low_level.h"
#include "servotestfunction.h"

// Initialize components
static auto hxm = HexapodManger();
// static const char *legs[] = {
//     kLeftFrontLeg,  kLeftMidLeg,  kLeftBackLeg,
//     kRightFrontLeg, kRightMidLeg, kRightBackLeg,
// };

unsigned char* p = nullptr;

void setup() {
  Serial.begin(115200);
  Serial.write('S');
  Serial.write('r');
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(8, INPUT);
  digitalWrite(8, 1);
  delay(500);
  sei();
  Wire.begin();
  TWSR = 3;   // no prescaler
  TWBR = 18;  // Set I2C speed lower to suite I2C Servo controller
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  delay(500);
  Serial.println("\n********* End Setup *********");
}

void loop() {
  testservo(&hxm);
  UserCode(&hxm);
  delay(50);
}
