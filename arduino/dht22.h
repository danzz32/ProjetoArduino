#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT22

class dht22 {
private:
  float umidade;
  float temperatura;
  DHT dht;
  LiquidCrystal_I2C lcd;  // Adicionando objeto para o display LCD
  
public:
  dht22() : dht(DHTPIN, DHTTYPE), lcd(0x27, 16, 2) {
    this->umidade = 0;
    this->temperatura = 0;
    lcd.init();       // Inicializa o LCD
    lcd.backlight();  // Liga a luz de fundo do LCD
  }

  void medicao() {
    delay(3000);

    umidade = dht.readHumidity();
    temperatura = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      return;
    }
    exibeResultados();
  }

  void exibeResultados() {
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println("%");
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println("°C ");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(temperatura);
    lcd.print(" *C");
    lcd.setCursor(0, 1);
    lcd.print("U:");
    lcd.print(umidade);
    lcd.print("%");
  }

  float getTemperatura() {
    return this->temperatura;
  }

  float getUmidade() {
    return this->umidade;
  }
};
