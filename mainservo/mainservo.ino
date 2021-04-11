#include "constants.h"
#include "hexapodleg.h"
#include "hexapodmanager.h"
#include "servotestfunction.h"
#include "servorosnode.h"

// Initialize components
auto *hxm = HexapodManger::getInstance();
static const char *legs[] = {
    kLeftFrontLeg,  kLeftMidLeg,  kLeftBackLeg,
    kRightFrontLeg, kRightMidLeg, kRightBackLeg,
};

void setup() {
  Serial.begin(115200);
  Serial.print("initialize legs connected to pin");
  auto *hxm = HexapodManger::getInstance();
  for (int i = 0; i < kPins; i=i+3) {
    int index = i / 3;
    hxm->connectLeg(i, i + 1, i + 2, i + 3);
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
