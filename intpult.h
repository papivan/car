#define PWMPOWERMIN 950 // Минимальное состоянние PWM управления от приемника
#define PWMPOWERMAX 2100 // Максимальное состояние PWM управления от приемника

 

#define MAXTIME 21000
#define MAXTIMECANAL 2100
#define pinCanal1 13
#define pinCanal2 14
#define pinCanal3 27
#define pinCanal4 26
#define DELTA 5 //Через сколько микросекунд начинается 

bool Canal1, Canal2, Canal3, Canal4; bool ScanC1, ScanC2, ScanC3, ScanC4; bool flagCanal1, flagCanal2, flagCanal3, flagCanal4;
bool C1Err,  C2Err, C3Err, C4Err, C5Err, CSErr; uint16_t Canal1Timeoff, Canal2Timeoff, Canal3Timeoff, Canal4Timeoff;
uint16_t Canal1Time, Canal2Time, Canal3Time, Canal4Time;
// Перед запуском: // 1. Поднимаем ScanC1=true // 2. Canal1Time = 0; // 3. Canal1Timeoff =0;
// 4. Canal1 = true; //На случай, если начали считывание с 1, нужн ждать пока она кончится
// 5. flagCanal1 = false; //Начало нормального импульса
void setup_CHANEL()
{
  pinMode(pinCanal1, INPUT);
  pinMode(pinCanal2, INPUT);
  pinMode(pinCanal3, INPUT);
  pinMode(pinCanal4, INPUT);
}

void ScanCHANEL()
{
  uint32_t LERRUA;
  ScanC1 = true; ScanC2 = true; ScanC3 = true; ScanC4 = true;  Canal1Time = 0; Canal2Time = 0; Canal3Time = 0; Canal4Time = 0;
  Canal1Timeoff = 0; Canal2Timeoff = 0; Canal3Timeoff = 0; Canal4Timeoff = 0;  Canal1 = true; Canal2 = true; Canal3 = true; Canal4 = true;
  flagCanal1 = false; flagCanal2 = false; flagCanal3 = false; flagCanal4 = false;  C1Err = false; C2Err = false; C3Err = false; C4Err = false;
  unsigned long tt, tectime, end_time;

  tectime = micros();
  end_time = tectime + MAXTIME + DELTA;
  while ((tectime < end_time) && (ScanC1 || ScanC2 || ScanC3 || ScanC4 ))
  {
    //====== C1
    if (ScanC1) //Если поднято считывание с канала
    {
      if (flagCanal1) // Если поднят расчет длины импульса
      {
        Canal1 = digitalRead(pinCanal1);
        if (Canal1) {
          Canal1Time += DELTA;
          if (Canal1Time > MAXTIMECANAL) {
            C1Err = true;
            ScanC1 = false;
          }
        }
        else        {
          ScanC1 = false;
        }
      }
      else //Если не поднят флаг расчет длины импульса
      {
        if (Canal1) //Если в канале 1, то мы в начале
        {
          Canal1 = digitalRead(pinCanal1);
        }
        else
        {
          Canal1 = digitalRead(pinCanal1);
          if (Canal1)
          {
            Canal1Time = DELTA;
            flagCanal1 = true;
          }
          else
          {
            Canal1Timeoff += DELTA; if (Canal1Timeoff > MAXTIME) ScanC1 = false; //Завершили
          }
        }
      }
    }
    //============= C2
    if (ScanC2) //Если поднято считывание с канала
    {
      if (flagCanal2) // Если поднят расчет длины импульса
      {
        Canal2 = digitalRead(pinCanal2);
        if (Canal2) {
          Canal2Time += DELTA;
          if (Canal2Time > MAXTIMECANAL)
          {
            C2Err = true;
            ScanC2 = false;
          }
        }
        else
        {
          ScanC2 = false;
        }
      }
      else //Если не поднят флаг расчет длины импульса
      {
        if (Canal2) //Если в канале 1, то мы в начале
        {
          Canal2 = digitalRead(pinCanal2);
        }
        else
        {
          Canal2 = digitalRead(pinCanal2);
          if (Canal2)
          {
            Canal2Time = DELTA;
            flagCanal2 = true;
          }
          else
          {
            Canal2Timeoff += DELTA; if (Canal2Timeoff > MAXTIME) ScanC2 = false; //Завершили
          }
        }
      }
    }
    //===== C3
    if (ScanC3) //Если поднято считывание с канала
    {
      if (flagCanal3) // Если поднят расчет длины импульса
      {
        Canal3 = digitalRead(pinCanal3);
        if (Canal3) {
          Canal3Time += DELTA;
          if (Canal3Time > MAXTIMECANAL)
          {
            C3Err = true;
            ScanC3 = false;
          }
        }
        else
        {
          ScanC3 = false;
        }
      }
      else //Если не поднят флаг расчет длины импульса
      {
        if (Canal3) //Если в канале 1, то мы в начале
        {
          Canal3 = digitalRead(pinCanal3);
        }
        else
        {
          Canal3 = digitalRead(pinCanal3);
          if (Canal3)
          {
            Canal3Time = DELTA;
            flagCanal3 = true;
          }
          else
          {
            Canal3Timeoff += DELTA; if (Canal3Timeoff > MAXTIME) ScanC3 = false; //Завершили
          }
        }
      }
    }
    //===== C4
    if (ScanC4) //Если поднято считывание с канала
    {
      if (flagCanal4) // Если поднят расчет длины импульса
      {
        Canal4 = digitalRead(pinCanal4);
        if (Canal4) {
          Canal4Time += DELTA;
          if (Canal4Time > MAXTIMECANAL)
          {
            C4Err = true;
            ScanC4 = false;
          }
        }
        else
        {
          ScanC4 = false;
        }
      }
      else //Если не поднят флаг расчет длины импульса
      {
        if (Canal4) //Если в канале 1, то мы в начале
        {
          Canal4 = digitalRead(pinCanal4);
        }
        else
        {
          Canal4 = digitalRead(pinCanal4);
          if (Canal4)
          {
            Canal4Time = DELTA;
            flagCanal4 = true;
          }
          else
          {
            Canal4Timeoff += DELTA; if (Canal4Timeoff > MAXTIME) ScanC4 = false; //Завершили
          }
        }
      }
    }
    tt = micros();
    while (tt < tectime)     tt = micros();
    tectime = tt + DELTA;
  }
}