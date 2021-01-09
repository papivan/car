#ifndef FLYSKY_PWM
#define FLYSKY_PWM

#define PWMPOWERMIN 950 // Минимальное состоянние PWM управления от приемника
#define PWMPOWERMAX 2100 // Максимальное состояние PWM управления от приемника

#define MAXTIME 21000
#define MAXTIMECANAL 2100
#define DELTA 5 //Через сколько микросекунд начинается 


struct Canal
{
  int pin = 0; // #define pinCanal1 13
  bool canal; //bool Canal1, Canal2, Canal3, Canal4;
  bool scan; //bool ScanC1, ScanC2, ScanC3, ScanC4; 
  bool flag; //bool flagCanal1, flagCanal2, flagCanal3, flagCanal4;
  bool err; // bool C1Err,  C2Err, C3Err, C4Err, C5Err, CSErr; 
  uint16_t timeoff; // uint16_t Canal1Timeoff, Canal2Timeoff, Canal3Timeoff, Canal4Timeoff;
  uint16_t chTime; // uint16_t Canal1Time, Canal2Time, Canal3Time, Canal4Time;

  void reset() {
    scan = true;
    chTime = 0;
    timeoff = 0;
    canal = true;
    flag = false;
    err = false;
  }
  
  void perform_scan() {
    if (!scan)
      return;
    
    //Если поднято считывание с канала
    if (flag) {
      // Если поднят расчет длины импульса
      canal = digitalRead(pin);
      if (canal) {
        chTime += DELTA;
        if (chTime > MAXTIMECANAL) {
          err = true;
          scan = false;
        }
      } else {
        scan = false;
      }
    } else {
      //Если не поднят флаг расчет длины импульса
      if (canal) {
        //Если в канале 1, то мы в начале
        canal = digitalRead(pin);
      } else {
        canal = digitalRead(pin);
        if (canal) {
          chTime = DELTA;
          flag = true;
        } else {
          timeoff += DELTA; if (timeoff > MAXTIME) scan = false; //Завершили
        }
      }
    }
  }
}; // struct Canal

struct FlySkyCanals {
  FlySkyCanals(int ch1 = 0, int ch2 = 0,
  int ch3 = 0, int ch4 = 0) {
    if(!ch1)
      return;
    canals[chNum++].pin = ch1;

    if(!ch2)
      return;
    canals[chNum++].pin = ch2;

    if(!ch3)
      return;
    canals[chNum++].pin = ch3;

    if(!ch4)
      return;
    canals[chNum++].pin = ch4;
  }

  void setup() const {
    for(int i=0; i<chNum; ++i)
      if(canals[i].pin)
        pinMode(canals[i].pin, INPUT);
  }

  void scan() {
    // Перед запуском: // 1. Поднимаем ScanC1=true // 2. Canal1Time = 0; // 3. Canal1Timeoff =0;
    // 4. Canal1 = true; //На случай, если начали считывание с 1, нужн ждать пока она кончится
    // 5. flagCanal1 = false; //Начало нормального импульса
    for(int i=0; i<chNum; ++i) 
      canals[i].reset();
      
    unsigned long tt, tectime, end_time;
  
    tectime = micros();
    end_time = tectime + MAXTIME + DELTA;
    while (tectime < end_time) {
      bool has_any_scan = false;
      for(int i=0; i<chNum; ++i)
        has_any_scan |= canals[i].scan;
      if(!has_any_scan)
        break;
      
      for(int i=0; i<chNum; ++i)
        canals[i].perform_scan();
      
      tt = micros();
      while (tt < tectime)
        tt = micros();
      tectime = tt + DELTA;
    }
  } // void scan()

  int chNum=0;
  const static int maxChNum = 4;
  Canal canals[maxChNum];
}; // struct FlySkyCanals

#endif // FLYSKY_PWM
