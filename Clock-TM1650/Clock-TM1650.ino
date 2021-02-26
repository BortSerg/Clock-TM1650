#include <Wire.h>
#include <TM1650.h>
#include <DS3231.h>
#include <BME280I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Ticker.h>

Ticker timer05s;
byte t05s;
byte workmode = 0;
byte hh, mmi, ss, dd, mmo, yy;

TM1650 Disp4Seg;

DS3231 Clock;
bool Century = false;
bool h12;
bool PM;
char* week[] = {"DUM", "Вск", "Пнд", "Втр", "Срд", "Чтв", "Птн", "Суб"};

BME280I2C::Settings settings(
  BME280::OSR_X1,
  BME280::OSR_X1,
  BME280::OSR_X1,
  BME280::Mode_Forced,
  BME280::StandbyTime_1000ms,
  BME280::Filter_Off,
  BME280::SpiEnable_False,
  0x76 // I2C address. I2C specific.
);
BME280I2C bme(settings);

// I2C pins
#define SDA_pin 4
#define SCL_pin 5



void setup(){
  
}

void loop(){
  
}
