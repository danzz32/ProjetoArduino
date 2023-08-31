#include <Wire.h>
#include "../lib/LiquidCrystal_I2C/LiquidCrystal_I2C.h"
#include "../lib/DHT/dht.h"
#include "data.h"
// #include "connection.h"

#define clk 6
#define dat 7
#define rst 8

const int pinoDHT11 = T4;
dht sensor;               // Sensor para medir temperatura e umidade
LiquidCrystal_I2C *lcd = new LiquidCrystal_I2C(0x27, 20, 4);
Data *date = new Data(clk, dat, rst);
// Connection *database = new Connection(date, &sensor);

void LerSensor();
void DataAtual();
void DiaAtual(int numDia);

void setup()
{
  Serial.begin(9600);
  delay(2000);
  lcd->init();
  lcd->backlight();
  // database->begin();
}

void loop()
{
  LerSensor();
  delay(3000);
  DataAtual();
  delay(3000);
  // database->run();
}

void LerSensor()
{
  sensor.read11(pinoDHT11);
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("U = ");
  lcd->print(sensor.humidity);
  lcd->print("%");
  lcd->setCursor(0, 1);
  lcd->print("T = ");
  lcd->print(sensor.temperature);
  lcd->print("*C");
}

void DataAtual()
{
  date->atualizar();
  lcd->clear();
  lcd->setCursor(0, 0);
  DiaAtual(date->getNumDia());
  lcd->print(date->dataAtual());
  lcd->setCursor(0, 1);
  lcd->print(date->horarioAtual());
}

void DiaAtual(int numDia)
{
  switch (numDia)
  {
  case 1:
    lcd->print("Dom ");
    break;
  case 2:
    lcd->print("Seg ");
    break;
  case 3:
    lcd->print("Ter ");
    break;
  case 4:
    lcd->print("Qua ");
    break;
  case 5:
    lcd->print("Qui ");
    break;
  case 6:
    lcd->print("Sex ");
    break;
  case 7:
    lcd->print("Sab ");
    break;
  }
}