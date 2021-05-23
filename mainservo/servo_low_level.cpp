#include "servo_low_level.h"

#include <Arduino.h>
#include <Wire.h>

#include "constants.h"

#define servo1 (16 >> 1)
#define servo2 (18 >> 1)
#define UART_BAUD_RATE 115200
#define LED_PIN 13

#define SERIAL_BUFFER_SIZE 256

#define MINIMUM_DELAY_MICROSECOND 240

char LEDState = 0;

void CheckEndMovement(void) {
  if (I2C_SERVOEND()) {
    Serial.write('X');
  } else {
    Serial.write('G');
  }

  LEDToggle();
}

void I2C_SERVOSET(unsigned char servo_num, unsigned int servo_pos) {
  if (servo_pos < MIN_SERVO_POSITION) {
    servo_pos = MIN_SERVO_POSITION;
  }
  if (servo_pos > MAX_SERVO_POSITION) {
    servo_pos = MAX_SERVO_POSITION;
  }

  if (servo_pos > 501) {
    servo_pos = (((servo_pos - 2) * 2) - 1000);
  } else {
    servo_pos = 0;
  }

  if (servo_num < 19) {
    Wire.beginTransmission(servo1);
  } else {
    Wire.beginTransmission(servo2);
  }
  Wire.write(servo_num - 1);
  Wire.write(servo_pos >> 8);
  Wire.write(servo_pos & 0XFF);
  Wire.endTransmission();
}

void I2C_SERVOMIN(unsigned char servo_num, unsigned int servo_pos) {
  if (servo_pos < MIN_SERVO_POSITION) {
    servo_pos = MIN_SERVO_POSITION;
  }

  if (servo_pos > MAX_SERVO_POSITION) {
    servo_pos = MAX_SERVO_POSITION;
  }

  servo_pos = ((servo_pos * 2) - 1000);

  if (servo_num < 19) {
    Wire.beginTransmission(servo1);
  } else {
    Wire.beginTransmission(servo2);
  }
  Wire.write((servo_num - 1) + (18 * 4));
  Wire.write(servo_pos >> 8);
  Wire.write(servo_pos & 0XFF);
  Wire.endTransmission();
  delay(20);
}

void I2C_SERVOMAX(unsigned char servo_num, unsigned int servo_pos) {
  if (servo_pos < MIN_SERVO_POSITION) {
    servo_pos = MIN_SERVO_POSITION;
  }

  if (servo_pos > MAX_SERVO_POSITION) {
    servo_pos = MAX_SERVO_POSITION;
  }

  servo_pos = ((servo_pos * 2) - 1000);

  if (servo_num < 19) {
    Wire.beginTransmission(servo1);
  } else {
    Wire.beginTransmission(servo2);
  }
  Wire.write((servo_num - 1) + (18 * 3));
  Wire.write(servo_pos >> 8);
  Wire.write(servo_pos & 0XFF);
  Wire.endTransmission();
  delay(20);
}

void I2C_SERVONUTRALSET(unsigned char servo_num, unsigned int servo_pos) {
  if (servo_pos < MIN_SERVO_POSITION) {
    servo_pos = MIN_SERVO_POSITION;
  }

  if (servo_pos > MAX_SERVO_POSITION) {
    servo_pos = MAX_SERVO_POSITION;
  }
  servo_pos = ((servo_pos * 2) - 1000);

  if (servo_num < 19) {
    Wire.beginTransmission(servo1);
  } else {
    Wire.beginTransmission(servo2);
  }
  Wire.write((servo_num - 1) + (18 * 5));
  Wire.write(servo_pos >> 8);
  Wire.write(servo_pos & 0XFF);
  Wire.endTransmission();
}

void I2C_SERVOSPEED(unsigned char value) {
  Wire.beginTransmission(servo1);
  Wire.write(18 * 2);
  Wire.write(value);
  Wire.write(0);
  Wire.endTransmission();
  Wire.beginTransmission(servo2);
  Wire.write(18 * 2);
  Wire.write(value);
  Wire.write(0);
  Wire.endTransmission();
  delay(20);
}

void I2C_SERVOOFFSET(unsigned char servo_num, int value) {
  value = 3000 - value;
  value = value - MID_SERVO_POSITION;

  if (value < -MIN_SERVO_POSITION) {
    value = -MIN_SERVO_POSITION;
  }

  if (value > MIN_SERVO_POSITION) {
    value = MIN_SERVO_POSITION;
  }

  if (value > 0) {
    value = 2000 + (value * 2);
  } else if (value <= 0) {
    value = -value * 2;
  }

  if (servo_num < 19) {
    Wire.beginTransmission(servo1);
  } else {
    Wire.beginTransmission(servo2);
  }
  Wire.write((servo_num - 1) + (18 * 6));
  Wire.write(value >> 8);
  Wire.write(value & 0XFF);
  Wire.endTransmission();
  delay(20);
}

void I2C_SERVOREVERSE(unsigned char servo_num, unsigned char servo_dir) {
  servo_dir = servo_dir > 0 ? 1 : 0;
  if (servo_num < 19) {
    Wire.beginTransmission(servo1);
  } else {
    Wire.beginTransmission(servo2);
  }
  Wire.write((servo_num - 1) + (18 * 7));
  Wire.write(servo_dir);
  Wire.write(0);
  Wire.endTransmission();
  delay(20);
}

char I2C_SERVOEND(void) {
  char buffer{};
  Wire.beginTransmission(servo1);
  int n = Wire.write(181);
  if (n != 1) {
    return -10;
  }

  n = Wire.endTransmission(false);
  if (n != 0) {
    return n;
  }

  delayMicroseconds(MINIMUM_DELAY_MICROSECOND);
  Wire.requestFrom(servo1, 1, true);
  while (Wire.available()) {
    buffer = Wire.read();
  }

  return (buffer);
}

int I2C_SERVOGET(int servo_num) {
  uint8_t buffer[2]{};
  Wire.beginTransmission(servo1);

  int n = Wire.write((servo_num - 1) + (18 * 8));
  if (n != 1) {
    return -10;
  }

  n = Wire.endTransmission(false);
  if (n != 0) {
    return n;
  }

  delayMicroseconds(MINIMUM_DELAY_MICROSECOND);
  Wire.requestFrom(servo1, 2, true);
  int i = 0;
  while (Wire.available() && i < 2) {
    buffer[i++] = Wire.read();
  }
  if (i != 2) {
    return -11;
  }
  return (((buffer[0] * 256 + buffer[1]) + 4) / 2 + MIN_SERVO_POSITION);
}

int I2C_SERVOGETOFFSET(int servo_num) {
  uint8_t buffer[2]{};
  Wire.beginTransmission(servo1);

  int n = Wire.write((servo_num - 1) + (182));
  if (n != 1) {
    return -10;
  }

  n = Wire.endTransmission(false);
  if (n != 0) {
    return n;
  }

  delayMicroseconds(MINIMUM_DELAY_MICROSECOND);
  Wire.requestFrom(servo1, 2, true);
  int i = 0;
  while (Wire.available() && i < 2) {
    buffer[i++] = Wire.read();
  }
  if (i != 2) return (-11);
  i = ((buffer[0] * 256 + buffer[1]));
  if (i > 2000) {
    return (3000 - (((i - 2000) / 2) + MID_SERVO_POSITION));
  } else {
    return (3000 - ((-i / 2) + MID_SERVO_POSITION));
  }
}

void ServoSetAll(ServoManager ptr_servo_motor[]) {
  for (short i = 0; i < kPins; i++) {
    if (ptr_servo_motor[i].getMappedAngle() >=
        (unsigned int)MIN_SERVO_POSITION) {
      I2C_SERVOSET(ptr_servo_motor[i].getPin(),
                   ptr_servo_motor[i].getMappedAngle());
    }
  }
  while (!I2C_SERVOEND()) {
    Serial.println("waiting to end I2C communication");
    delay(1);
  }
  LEDToggle();
}

void LEDToggle(void) {
  LEDState = LEDState == LOW ? HIGH : LOW;
  digitalWrite(LED_PIN, LEDState);
}

void UserCode(HexapodManger *hxm) {
  // Configuration
  auto *servos = hxm->getServos();
  for (short i = 0; i < kPins; i++) {
    // setup maximum value
    I2C_SERVOMAX(servos[i].getPin(), MAX_SERVO_POSITION);
    // setup minimum values
    I2C_SERVOMIN(servos[i].getPin(), MIN_SERVO_POSITION);
    // setup offset values
    I2C_SERVOOFFSET(servos[i].getPin(), MID_SERVO_POSITION);
    // setup directions (Servo Reverse)
    I2C_SERVOREVERSE(servos[i].getPin(), 0);
    // set servomotor speed
    // I2C_SERVOSPEED(getSpeed());
  }
  // update all servos
  ServoSetAll(servos);
}