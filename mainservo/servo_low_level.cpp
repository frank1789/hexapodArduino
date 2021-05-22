#include "servo_low_level.h"

#include <Arduino.h>
#include <Wire.h>

#define servo1 (16 >> 1)
#define servo2 (18 >> 1)
#define UART_BAUD_RATE 115200
#define LED_PIN 13

#define SERIAL_BUFFER_SIZE 256

#define MINIMUM_DELAY_MICROSECOND 240

#define MIN_SERVO_POSITION 500
#define MID_SERVO_POSITION 1500
#define MAX_SERVO_POSITION 2500

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
  if (servo_pos < 500) {
    servo_pos = 500;
  } else if (servo_pos > 2500) {
    servo_pos = 2500;
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
  if (servo_pos < 500) {
    servo_pos = 500;
  } else if (servo_pos > 2500) {
    servo_pos = 2500;
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
  if (servo_pos < 500) {
    servo_pos = 500;
  } else if (servo_pos > 2500) {
    servo_pos = 2500;
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
  if (servo_pos < 500) {
    servo_pos = 500;
  } else if (servo_pos > 2500) {
    servo_pos = 2500;
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
  value = value - 1500;

  if (value < -500) {
    value = -500;
  } else if (value > 500) {
    value = 500;
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

  delayMicroseconds(350);
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
  return (((buffer[0] * 256 + buffer[1]) + 4) / 2 + 500);
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
    return (3000 - (((i - 2000) / 2) + 1500));
  } else {
    return (3000 - ((-i / 2) + 1500));
  }
}

void ServoSetAll(unsigned int Servo1, unsigned int Servo2, unsigned int Servo3,
                 unsigned int Servo4, unsigned int Servo5, unsigned int Servo6,
                 unsigned int Servo7, unsigned int Servo8, unsigned int Servo9,
                 unsigned int Servo10, unsigned int Servo11,
                 unsigned int Servo12, unsigned int Servo13,
                 unsigned int Servo14, unsigned int Servo15,
                 unsigned int Servo16, unsigned int Servo17,
                 unsigned int Servo18) {
  if (Servo1 >= 500) {
    I2C_SERVOSET(1, Servo1);
  }
  if (Servo2 >= 500) {
    I2C_SERVOSET(2, Servo2);
  }
  if (Servo3 >= 500) {
    I2C_SERVOSET(3, Servo3);
  }
  if (Servo4 >= 500) {
    I2C_SERVOSET(4, Servo4);
  }
  if (Servo5 >= 500) {
    I2C_SERVOSET(5, Servo5);
  }
  if (Servo6 > 500) {
    I2C_SERVOSET(6, Servo6);
  }
  if (Servo7 >= 500) {
    I2C_SERVOSET(7, Servo7);
  }
  if (Servo8 >= 500) {
    I2C_SERVOSET(8, Servo8);
  }
  if (Servo9 >= 500) {
    I2C_SERVOSET(9, Servo9);
  }
  if (Servo10 >= 500) {
    I2C_SERVOSET(10, Servo10);
  }
  if (Servo11 >= 500) {
    I2C_SERVOSET(11, Servo11);
  }
  if (Servo12 >= 500) {
    I2C_SERVOSET(12, Servo12);
  }
  if (Servo13 >= 500) {
    I2C_SERVOSET(13, Servo13);
  }
  if (Servo14 >= 500) {
    I2C_SERVOSET(14, Servo14);
  }
  if (Servo15 >= 500) {
    I2C_SERVOSET(15, Servo15);
  }
  if (Servo16 >= 500) {
    I2C_SERVOSET(16, Servo16);
  }
  if (Servo17 >= 500) {
    I2C_SERVOSET(17, Servo17);
  }
  if (Servo18 >= 500) {
    I2C_SERVOSET(18, Servo18);
  }
  while (!I2C_SERVOEND()) {
    delay(1);
  }
  LEDToggle();
}

void LEDToggle(void) {
  if (LEDState == 0)
    LEDState = 1;
  else
    LEDState = 0;
  digitalWrite(LED_PIN, LEDState);
}

void UserCode(void) {
  //------------------------------Configuration------------------------------

  I2C_SERVOMAX(1, 2500);
  I2C_SERVOMAX(2, 2500);
  I2C_SERVOMAX(3, 2500);
  I2C_SERVOMAX(4, 2500);
  I2C_SERVOMAX(5, 2500);
  I2C_SERVOMAX(6, 2500);
  I2C_SERVOMAX(7, 2500);
  I2C_SERVOMAX(8, 2500);
  I2C_SERVOMAX(9, 2500);
  I2C_SERVOMAX(10, 2500);
  I2C_SERVOMAX(11, 2500);
  I2C_SERVOMAX(12, 2500);
  I2C_SERVOMAX(13, 2500);
  I2C_SERVOMAX(14, 2500);
  I2C_SERVOMAX(15, 2500);
  I2C_SERVOMAX(16, 2500);
  I2C_SERVOMAX(17, 2500);
  I2C_SERVOMAX(18, 2500);  // Maximum Values

  I2C_SERVOMIN(1, 500);
  I2C_SERVOMIN(2, 500);
  I2C_SERVOMIN(3, 500);
  I2C_SERVOMIN(4, 500);
  I2C_SERVOMIN(5, 500);
  I2C_SERVOMIN(6, 500);
  I2C_SERVOMIN(7, 500);
  I2C_SERVOMIN(8, 500);
  I2C_SERVOMIN(9, 500);
  I2C_SERVOMIN(10, 500);
  I2C_SERVOMIN(11, 500);
  I2C_SERVOMIN(12, 500);
  I2C_SERVOMIN(13, 500);
  I2C_SERVOMIN(14, 500);
  I2C_SERVOMIN(15, 500);
  I2C_SERVOMIN(16, 500);
  I2C_SERVOMIN(17, 500);
  I2C_SERVOMIN(18, 500);  // Minimum Values

  I2C_SERVOOFFSET(1, 1500);
  I2C_SERVOOFFSET(2, 1500);
  I2C_SERVOOFFSET(3, 1500);
  I2C_SERVOOFFSET(4, 1500);
  I2C_SERVOOFFSET(5, 1500);
  I2C_SERVOOFFSET(6, 1500);
  I2C_SERVOOFFSET(7, 1500);
  I2C_SERVOOFFSET(8, 1500);
  I2C_SERVOOFFSET(9, 1500);
  I2C_SERVOOFFSET(10, 1500);
  I2C_SERVOOFFSET(11, 1500);
  I2C_SERVOOFFSET(12, 1500);
  I2C_SERVOOFFSET(13, 1500);
  I2C_SERVOOFFSET(14, 1500);
  I2C_SERVOOFFSET(15, 1500);
  I2C_SERVOOFFSET(16, 1500);
  I2C_SERVOOFFSET(17, 1500);
  I2C_SERVOOFFSET(18, 1500);  // Offset Values

  I2C_SERVOREVERSE(1, 0);
  I2C_SERVOREVERSE(2, 0);
  I2C_SERVOREVERSE(3, 0);
  I2C_SERVOREVERSE(4, 0);
  I2C_SERVOREVERSE(5, 0);
  I2C_SERVOREVERSE(6, 0);
  I2C_SERVOREVERSE(7, 0);
  I2C_SERVOREVERSE(8, 0);
  I2C_SERVOREVERSE(9, 0);
  I2C_SERVOREVERSE(10, 0);
  I2C_SERVOREVERSE(11, 0);
  I2C_SERVOREVERSE(12, 0);
  I2C_SERVOREVERSE(13, 0);
  I2C_SERVOREVERSE(14, 0);
  I2C_SERVOREVERSE(15, 0);
  I2C_SERVOREVERSE(16, 0);
  I2C_SERVOREVERSE(17, 0);
  I2C_SERVOREVERSE(18, 0);  // Directions (Servo Reverse)

  //------------------------------Code Flow------------------------------

  ServoSetAll(1374, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500,
              1500, 1500, 1500, 1500, 1500, 1500, 1500);  // Line # 0
  delay(300);                                             // Default Delay
  ServoSetAll(1374, 1500, 1500, 1877, 1500, 1500, 1500, 1500, 2500, 1500, 1500,
              1500, 1500, 1500, 1500, 1500, 1500, 1500);  // Line # 1
  delay(300);                                             // Default Delay
  ServoSetAll(1374, 1500, 1500, 2500, 1500, 1500, 1500, 1500, 907, 1500, 1500,
              1500, 1500, 1500, 1500, 1500, 1500, 1500);  // Line # 2
  delay(300);                                             // Default Delay
  ServoSetAll(1374, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500,
              1500, 1500, 1500, 1500, 1500, 1500, 1500);  // Line # 3
  delay(300);                                             // Default Delay
}


void LowLevelControllerServo(unsigned char servo_num, unsigned int servo_position) {
	I2C_SERVOMAX(1, MAX_SERVO_POSITION);
	I2C_SERVOMIN(1, MIN_SERVO_POSITION);
	I2C_SERVOOFFSET(1, MID_SERVO_POSITION);
	I2C_SERVOREVERSE(1, 0);
	if (servo_position >= 500) {
    	I2C_SERVOSET(servo_num, servo_position);
  	}
  	while (!I2C_SERVOEND()) {
    	delay(1);
  	}
  	LEDToggle();
}