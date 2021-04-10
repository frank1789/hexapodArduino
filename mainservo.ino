#include "hexapodleg.h"
#include "servotestfunction.h"

class ServoManager {
 public:
  ServoManager(int pin) {
    servo_.attach(pin);
    resetServo();
  }

  void setServo(int angle) {
    if (angle >= 180) {
      angle = 179;
      servo_.write(angle);
    } else if (angle <= 0) {
      angle = 0;
      servo_.write(angle);
    } else {
      servo_.write(angle);
    }
  }

 protected:
  void resetServo() { servo_.write(90); }

 private:
  Servo servo_;
};

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
  for (int i = 0; i < 6; i + 3) {
    legs[i] = Leg(i + 1, i + 2, i + 3);
  }
}

void loop() { testservo(); }