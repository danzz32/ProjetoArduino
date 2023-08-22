#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup() {
  Wire.begin();

  // Inicialize o RTC
  if (!rtc.begin()) {
    Serial.println("Não foi possível encontrar um módulo RTC!");
    while (1) {}
  }

  // Se o RTC não estiver funcionando, configure a hora e a data manualmente
  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Inicialize a comunicação serial
  Serial.begin(9600);
}

void loop() {
  data date;
  date.dataAtual();
  date.horaAtual();
  delay(1000);
}
