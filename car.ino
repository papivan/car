#include "Motor.h"
#include "intpult.h"

Motor motor(25, 32,33);
FlySkyCanals flySky(13, 14, 27, 26);

void setup() {
  Serial.begin(115200);

  motor.setup();
  flySky.setup();
}
 
void loop() {
  motor.test();

  long mic;
  mic = micros();
  flySky.scan();
  
  mic = micros() - mic;
  Serial.print(mic); Serial.print(" = ");
  
  for(int i=0; i<flySky.chNum; ++i) {
    Serial.print(flySky.canals[i].chTime);
    Serial.print(" = ");
  }
  Serial.println("==========================================");
  delay(200);
}
