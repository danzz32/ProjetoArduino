#include "../lib/LiquidCrystal_I2C/LiquidCrystal_I2C.h"
#include "../lib/DHT/dht.h"
#include <Wire.h>
#include "data.h"

const int pinoDHT11 = A2; // PINO ANALÓGICO UTILIZADO PELO DHT11
dht DHT;                  // VARIÁVEL DO TIPO DHT
LiquidCrystal_I2C *lcd = new LiquidCrystal_I2C(0x27, 20, 4);
data *date = new data();

void LerSensor();
void Data();

void setup()
{
  Serial.begin(9600);
  delay(2000);
  lcd->init();
  lcd->backlight();
}

void loop()
{
  //LerSensor();
  Data();
  delay(1000);
}

void LerSensor()
{
  DHT.read11(pinoDHT11);
  lcd->setCursor(0, 0);
  lcd->print("U = ");
  lcd->print(DHT.humidity);
  lcd->print("%");
  lcd->setCursor(0, 1);
  lcd->print("T = ");
  lcd->print(DHT.temperature);
  lcd->print("*C");
}

void Data()
{
  lcd->setCursor(0, 0);
  lcd->clear();
  lcd->print(date->getDia());
  lcd->print("/");
  lcd->print(date->getMes());
  lcd->print("/");
  lcd->print(date->getAno());
}