//Projeto medir a temperatura e a umidade com DHT22
#include <DHT.h>//Inclui a biblioteca DHT Sensor Library
#include <LiquidCrystal_I2C.h>
#define DHTPIN 2//Pino digital 2 conectado ao DHT11
#define DHTTYPE DHT22//DHT 11

DHT dht(DHTPIN, DHTTYPE);//Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)

void setup() {
  Serial.begin(9600);//Inicializa a comunicação serial
  dht.begin();//Inicializa o sensor DHT22
}

void loop() {
  delay(3000);//Intervalo de dois segundos entre as medições

  float h = dht.readHumidity();//lê o valor da umidade e armazena na variável h do tipo float (aceita números com casas decimais)
  float t = dht.readTemperature();//lê o valor da temperatura e armazena na variável t do tipo float (aceita números com casas decimais)

  if (isnan(h) || isnan(t)) {//Verifica se a umidade ou temperatura são ou não um número
    return;//Caso não seja um número retorna
  }


  Serial.print("Umidade: ");//Imprime no monitor serial a mensagem "Umidade: "
  Serial.print(h);//Imprime na serial o valor da umidade
  Serial.println("%");//Imprime na serial o caractere "%" e salta para a próxima linha
  Serial.print("Temperatura: ");//Imprime no monitor serial a mensagem "Temperatura: "
  Serial.print(t);//Imprime na serial o valor da temperatura
  Serial.println("°C ");//Imprime no monitor serial "ºC" e salta para a próxima linha

  lcd.clear();
  lcd.setCursor(0,0);
  ldc.print("T:");
  lcd.print(t);
  lcd.print(" *C");
  lcd.setCursor(0,1);
  lcd.print("U:");
  lcd.print(u);
  lcd.print("%");
}

