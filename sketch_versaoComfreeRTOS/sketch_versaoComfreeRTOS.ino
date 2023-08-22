//inclusão das bibliotecas
#include <LiquidCrystal_I2C.h> //baixar no github
//#include <arduino_FreeRTOS.h>
//#include <HCS04.h>
#include <DHT.h> // versão 1.4.0 (by adafruit)

//AQUI DEFINIMOS OS PINOS NOS QUAIS O SENSOR ESTARÁ CONECTADO A PLACA ARDUINO
#define DHTPIN 2
#define DHTTYPE DHT22

//DECLARANDO OS OBJETOS QUE SERÃO UTILIZADOS
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);
float u; //variavel referente a umidade
float t; //variavel referente a temperatura 

//AQUI INICIALIZAMOS OS SENSORES E DISPOSITIVOS CONECTADOS A PLACA
void setup(){
  lcd.begin ();
  dht.begin();
  Serial.begin(9600);
  lcd.setBacklight(HIGH); //SETA A LUZ DE FUNDO DO DISPLAY LCD
  cTaskCreate(TaskDisplay, "Display", 1000, NULL, 1, NULL)
  cTaskCreate(TaskSerial, "Serial", 1000, NULL, 2, NULL)
  cTaskCreate(TaskDHT, "DHT", 1000, NULL, 3, NULL)
  void loop(){ //o void loop executará os comando alocados na função anterior infinitamente

  } 
  //A PARTIR DAQUI CHAMAREMOS AS TAREFAS A SEREM EXECUTADAS, SENDO ELAS O DISPLAY, A PORTA SERIAL E OS DADOS DO SENSOR DHT.
  void TaskDisplay(void *pvParameters){ //DENTRO DA FUNÇÃO É NECESSÁRIO CHAMAR OS PARÊMTROS ESTABELECIDOS ATRAVÉS DE *pvParameters
    for(;;){
      lcd.setCursor(0,0);
      ldc.print("T:");
      lcd.print(t);
      lcd.print(" *C");
       lcd.setCursor(0,1);
      lcd.print("U:");
      lcd.print(u);
      lcd.print("%");
      vTaskDelay(1000 / portTICK_PERIOD_MS;) //AQUI DETERMINAMOS UM DELAY DE 1 SEGUNDO
    }
  }
  void TaskSerial(void *pvParameters){
    for(;;){
      Serial.print("umidade: ");
      Serial.print("u");
      Serial.print("%");
      Serial.print("Temperatura: ");
      Serial.print(t);
      Serial.print(" *C");
       vTaskDelay(1000 / portTICK_PERIOD_MS;) //AQUI DETERMINAMOS UM DELAY DE 1 SEGUNDO

    }

  }
  void TaskDHT(void *pvParameters){
    for(;;){
      u = dht.readHumidity();
      t = dht.readTemperature();
       vTaskDelay(1000 / portTICK_PERIOD_MS;) //AQUI DETERMINAMOS UM DELAY DE 1 SEGUNDO
    }
  }
}
