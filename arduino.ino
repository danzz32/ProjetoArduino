#include "Credenciais.h"

#define MYSQL_DEBUG_PORT Serial
#define _MYSQL_LOGLEVEL_ 1

#include <MySQL_Generic.h>
#include <Arduino.h>
#include <DHT.h>

IPAddress server(85, 10, 205, 173);  // IP do DB
uint16_t server_port = 3306;

MySQL_Connection conn((Client *)&client);
MySQL_Query *query_mem;

#define DHTPIN 15      // Pino ao qual o sensor DHT está conectado
#define DHTTYPE DHT11  // Tipo de sensor DHT
DHT dht(DHTPIN, DHTTYPE);

void LerSensor();
void EnviaDados(float temperatura, float umidade);

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 5000);  // Aguarda a conexão com a porta Serial

  MYSQL_DISPLAY1("\nInicializando a placa  ", ARDUINO_BOARD);
  MYSQL_DISPLAY(MYSQL_MARIADB_GENERIC_VERSION);
  MYSQL_DISPLAY1("Conectando em ", ssid);

  WiFi.begin(ssid, pass); // Realiza a conexão com WiFi

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    MYSQL_DISPLAY0(".");
  }

  MYSQL_DISPLAY1("Conectado ao Wifi. My IP address is:", WiFi.localIP());
  MYSQL_DISPLAY3("Conectando ao servidor SQL @", server, ", Porta =", server_port);
}

void loop() {
  MYSQL_DISPLAY("Conectando..."); // Realizando conexão com o DB
  if (conn.connectNonBlocking(server, server_port, user, password) != RESULT_FAIL) {
    delay(500);
    LerSensor();
  } else {
    MYSQL_DISPLAY("\nFalha na conexão. Tentando novamente.");
  }
  delay(5000);
}

void LerSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(t) || isnan(h)) {
    Serial.println("Falha na leitura do sensor DHT");
  } else {
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.println("%");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println("°C");
    delay(10000);
    EnviaDados(t, h);
  }
}

void EnviaDados(float temperatura, float umidade) {
  MySQL_Query query_mem = MySQL_Query(&conn);

  if (conn.connected()) { // Envia os dados para o DB
    char INSERT_SQL[255];
    sprintf(INSERT_SQL, "INSERT INTO arduino_fmt1.registros (temperatura, umidade, data, horario) VALUES (%.2f, %.2f, CURDATE(), CONVERT_TZ(NOW(), 'UTC', 'America/Sao_Paulo'))", temperatura, umidade);
    MYSQL_DISPLAY(INSERT_SQL);

    if (!query_mem.execute(INSERT_SQL)) {
      MYSQL_DISPLAY("Erro no envio dos dados");
    } else {
      MYSQL_DISPLAY("Dados enviados!");
    }
  } else {
    MYSQL_DISPLAY("Desconectado do servidor. Impossível enviar os dados!");
  }
}