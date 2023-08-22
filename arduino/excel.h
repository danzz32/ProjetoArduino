#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <SD.h>

class excel {
private:
  String arquivo;
  std::vector<std::vector<String>> dados;

public:
  excel() {
    this->arquivo = "dados.csv";
    if (!SD.begin(SS)) {
      Serial.println("Falha ao inicializar o cartão SD!");
    }
  }

  void coletarDados() {
    float temperatura = lerSensorTemperatura();
    float umidade = lerSensorUmidade();
    String dataHora = obterDataHora();

    // Armazena os dados coletados em um vetor
    std::vector<String> registro;
    registro.push_back(String(temperatura));
    registro.push_back(String(umidade));
    registro.push_back(dataHora);
    dados.push_back(registro);
  }

  String formatarDados() {
    String dadosCSV = "";
    for (const std::vector<String>& linha : dados) {
      for (const String& campo : linha) {
        dadosCSV += campo + ";";
      }
      dadosCSV += "\n";
    }
    return dadosCSV;
  }

  void callback(char* topic, byte* payload, unsigned int length) {
    // Processa mensagens MQTT recebidas
    Serial.println("Mensagem MQTT recebida!");
    Serial.print("Tópico: ");
    Serial.println(topic);
    Serial.print("Mensagem: ");
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
  }

  float lerSensorTemperatura() {
    // adicionar leitura do seu sensor de temperatura
    return 25.5;  // Valor de exemplo
  }

  float lerSensorUmidade() {
    // adicionar leitura do sensor de umidade
    return 50.0;  // Valor de exemplo
  }

  String obterDataHora() {
    data date;
    std::ostringstream saida;
    saida << date.dataAtual() << ";" << date.horario();
    return saida.str();
  }
};
