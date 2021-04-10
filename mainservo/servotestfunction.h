#ifndef SERVOTESTFUNCTION_H
#define SERVOTESTFUNCTION_H

inline void testservo() {
  for (int i = 0; i < 6; i + 3) {
    legs[i].coxa.setServo(75);
    delay(500);
    legs[i].coxa.setServo(90);
    delay(500);
    legs[i].femur.setServo(120);
    delay(500);
    legs[i].femur.setServo(90);
    delay(500);
    legs[i].tibia.setServo(120);
    delay(500);
    legs[i].tibia.setServo(90);
  }
}

#endif  // SERVOTESTFUNCTION_H