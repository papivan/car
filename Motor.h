#ifndef CAR_MOTOR
#define CAR_MOTOR

struct Motor {
  Motor(int en, int dirA, int dirB)
  : enable1Pin(en)
  , motor1Pin1(dirA)
  , motor1Pin2(dirB)
  {}

  void setup() const {
    // sets the pins as outputs:
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enable1Pin, OUTPUT);
    
    // configure LED PWM functionalitites
//    ledcSetup(pwmChannel, freq, resolution);
    
    // attach the channel to the GPIO to be controlled
//    ledcAttachPin(enable1Pin, pwmChannel);
  }

  void test(bool full=false) {
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

private:
  int motor1Pin1 = -1;
  int motor1Pin2 = -1; 
  int enable1Pin = -1; 

   // Setting PWM properties
  const int freq = 30000;
  const int pwmChannel = 0;
  const int resolution = 8;
  int dutyCycle = 200;
};

#endif // CAR_MOTOR
