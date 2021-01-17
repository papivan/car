#ifndef CAR_MOTOR
#define CAR_MOTOR

#include <Arduino.h>

struct Motor {
  Motor(int en, int dirA, int dirB)
  : enable1Pin(en)
  , motor1Pin1(dirA)
  , motor1Pin2(dirB)
  {}

  void setup() const;

  void test(bool full=false);
  void stop(int speed=0);
  void moveFW(int speed=0, uint16_t val=0);
  void moveBW(int speed=0, uint16_t val = 0);
  
private:
  int motor1Pin1 = -1;
  int motor1Pin2 = -1; 
  int enable1Pin = -1; 

  int state = 0;
  
   // Setting PWM properties
  const int freq = 30000;
  const int pwmChannel = 0;
  const int resolution = 8;
  int dutyCycle = 200;
};

#endif // CAR_MOTOR
