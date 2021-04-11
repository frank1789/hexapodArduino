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
  for (int i = 0; i < kPins; i += 3) {
    Serial.println(i);
    int index = i / 3;
    int pin_coxa = i + 1;
    int pin_femur = i + 2;
    int pin_tibia = i + 3;
    auto msg = String(i + " ");
    msg += "setup leg: ";
    msg += String("\"") + legs[index] + String("\"") + String("\t");
    msg += "assign pins: ";
    msg += "coxa: ";
    msg += String(pin_coxa) + "\t";
    msg += "femur: ";
    msg += String(pin_femur) + "\t";
    msg += "tibia: ";
    msg += String(pin_tibia) + "\n";
    Serial.println(msg);
    hxm->connectLeg(index, pin_coxa, pin_femur, pin_tibia);
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
