#include "Motor.h"
Motor motor(2, 3, 4);

#define USE_FS_PWM

#ifdef USE_FS_PWM
  #include "intpult.h"
  FlySkyCanals flySky(14, 15, 16, 17);
  //FlySkyCanals flySky(15);
#else
  #include "FlySkyIBus.h"
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
 
uint16_t min_speed = 0;
uint16_t max_speed = 0;
void loop() {
//  motor.test(true); return;

#ifdef USE_FS_PWM
  long mic;
  mic = micros();
  flySky.scan();
  
  mic = micros() - mic;
//  Serial.print(mic); Serial.print(" = ");
  
//  for(int i=0; i<flySky.chNum; ++i) {
//    Serial.print(flySky.canals[i].chTime);
//    Serial.print(" = ");
//  }
//  Serial.println("==========================================");
//  delay(200);
  uint16_t speed = flySky.canals[0].chTime;
  if(!min_speed || speed<min_speed)
    min_speed = speed;
  if(!max_speed || speed>max_speed)
    max_speed = speed;
  uint16_t stop_speed = (min_speed+max_speed)/2;
  if(speed< stop_speed-10)
    motor.moveBW(speed, 1.*(stop_speed-speed)*255/(max_speed-stop_speed));
  else if(speed > stop_speed+10)
    motor.moveFW(speed, 1.*(speed-stop_speed)*255/(max_speed-stop_speed));
  else
    motor.stop(speed);


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
