#include "Motor.h"
#include <Arduino.h>

void Motor::setup() const {
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  
  // configure LED PWM functionalitites
//    ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
//    ledcAttachPin(enable1Pin, pwmChannel);
}

void Motor::test(bool full) {
  // testing
  Serial.println("Testing DC Motor...");

  analogWrite(enable1Pin, 130);
  // Move the DC motor forward at maximum speed
  Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  delay(2000);
 
  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(1000);
 
  // Move DC motor backwards at maximum speed
  Serial.println("Moving Backwards");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  delay(2000);
 
  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(1000);

 if(!full)
  return;
  // Move DC motor forward with increasing speed
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  while (dutyCycle <= 255){
//      ledcWrite(pwmChannel, dutyCycle);   
    analogWrite(enable1Pin, dutyCycle);
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  dutyCycle = 200;
}


void Motor::stop(int speed) {
  if(state == 1) return;
  state = 1;
  // Stop the DC motor
  Serial.print("Motor stopped");
  if(speed) {
    Serial.print(" speed:");
    Serial.print(speed);
  }
  Serial.println("");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  analogWrite(enable1Pin, 0); 
}

void Motor::moveFW(int speed, uint16_t val) {
//    if(state == 2) return;
  state = 2;
  // Move the DC motor forward at maximum speed
  Serial.print("Moving Forward");
  if(speed) {
    Serial.print(" speed:");
    Serial.print(speed);
  }
  if(val) {
    Serial.print(" val:");
    Serial.print(val);
    if(val>255)
    val = 255;
  } else
    val = 255;
  Serial.println("");
  digitalWrite(motor1Pin2, HIGH); 
  digitalWrite(motor1Pin1, LOW);
//    dutyCycle = 130;
//    while (dutyCycle <= 255){
////      ledcWrite(pwmChannel, dutyCycle);   
//      analogWrite(enable1Pin, dutyCycle);
//      Serial.print("Forward with duty cycle: ");
//      Serial.println(dutyCycle);
//      dutyCycle = dutyCycle + 5;
//      delay(500);
//    }
  analogWrite(enable1Pin, val); 
}

void Motor::moveBW(int speed, uint16_t val) {
//    if(state == 3) return;
  state = 3;
  // Move DC motor backwards at maximum speed
  Serial.print("Moving Backwards");
  if(speed) {
    Serial.print(" speed:");
    Serial.print(speed);
  }
  if(val) {
    Serial.print(" val:");
    Serial.print(val);
    if(val>255)
    val = 255;
  } else
    val = 255;
  Serial.println("");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  analogWrite(enable1Pin, val);  
}
