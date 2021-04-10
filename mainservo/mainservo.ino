#include "hexapodleg.h"
#include "servotestfunction.h"


struct Leg {
  Leg(int pin_coxa, int pin_femur, int pin_tibia) {
    coxa(pin_coxa);
    femur(pin_femur);
    tibia(pin_tibia);
  }

  ServoManager coxa;
  ServoManager femur;
  ServoManager tibia;
};

static Leg legs[6];

void setup() {
  for (int i = 0; i < 6; i=i + 3) {
    legs[i] = Leg(i + 1, i + 2, i + 3);
  }
}

void loop() { testservo(); }
