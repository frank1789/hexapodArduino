#include "constants.h"
#include "hexapodleg.h"
#include "hexapodmanager.h"
#include "servotestfunction.h"

// Initialize components
auto *hxm = HexapodManger::getInstance();
static const char *legs[] = {
    kLeftFrontLeg,  kLeftMidLeg,  kLeftBackLeg,
    kRightFrontLeg, kRightMidLeg, kRightBackLeg,
};

void setup() {
  Serial.begin(115200);
  Serial.print("initialize legs connected to pin\n");
  auto *hxm = HexapodManger::getInstance();
  for (int i = 0; i < kPins; i=i+3) {
    int index = i / 3;
    Serial.print("setup leg: ");
    Serial.println(legs[index]);
    Serial.println("assign pins: ");
    Serial.println("coxa: ");
    Serial.println(i+1);
    Serial.println("femur: ");
    Serial.println(i+2);
    Serial.println("tibia: ");
    Serial.println(i+3);
    hxm->connectLeg(index, i + 1, i + 2, i + 3);
  }
}

void loop() {
  for (int i = 0; i < kNumberLegs; i++) {
    auto name_leg = legs[i];
    auto tleg = HexapodManger::getInstance()->getLeg(name_leg);
    Serial.print("test leg: ");
    Serial.println(name_leg);
    testservo(tleg);
  }
}
