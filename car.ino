#include "Motor.h"
#include "intpult.h"
#include "FlySkyIBus.h"


#define USE_FS_PWM

Motor motor(25, 32,33);
#ifdef USE_FS_PWM
FlySkyCanals flySky(13, 14, 27, 26);
#else
HardwareSerial FSkySerial(1);
uint16_t ChVal[10];
uint16_t ChValOld[10];
#endif

void setup() {
  Serial.begin(115200);

  motor.setup();
#ifdef USE_FS_PWM
  flySky.setup();
#else
  IBus.begin(FSkySerial);
  for(int i=0; i<10; ++i) {
    ChVal[i] = 0;
    ChValOld[i] = 0;
  }
#endif
}
 
void loop() {
  motor.test();

#ifdef USE_FS_PWM
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

#else
  
  IBus.loop();

  bool changed = false;
  for(int i=0; i<10; ++i) {
    ChVal[i] = IBus.readChannel(i);
    changed = (ChVal[i]-ChValOld[i]) > 5;
  }
  char buf[50];
  if(changed) {
    for(int i=0; i<10; ++i) {
      ChValOld[i] = ChVal[i];
      sprintf(buf, "Ch%d   %d", i, ChVal[i]);
      Serial.println(buf);
    }
    Serial.println("==================================================");
//    sendFlySkyVoltage(15);
    delay(10);
  }
  
//  delay(45);
//  sendFlySkyVoltage(4);
#endif
}

//void sendFlySkyVoltage(uint16_t voltage) {
//  uint8_t first = voltage;
//  uint8_t second = voltage >> 8;
//  FSkySerial.write( 0x06);
//  FSkySerial.write( 0xA1);
//  FSkySerial.write( first);
//  FSkySerial.write( second);
//
//  uint16_t checksum = ~(0x06 + 0xA1 + first + second);
//  FSkySerial.write(checksum & 0xFF);
//  FSkySerial.write( checksum >> 8);
//}
