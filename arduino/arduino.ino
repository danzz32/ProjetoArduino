#include <Wire.h>
#include "DHT/DHT.h"
#include "util/*"
#include "LiquidCrystal_I2C/LiquidCrystal_I2C.h"
#include "RTCLib/src/RTCLib.h"

RTC_DS3231 rtc;
data date;
dht22 sensor;
excel planilha;

void setup() {
  Wire.begin();

  if (!rtc.begin()) {
    Serial.println("Não foi possível encontrar um módulo RTC!");
    while (1) {}
  }

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  Serial.begin(9600);
  sensor.begin();
}

void loop() {
  date.exibeDataHora();
}
