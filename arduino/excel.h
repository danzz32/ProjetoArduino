#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <SD.h>

class ExcelExporter {
private:
  String arquivo;
  std::vector<std::vector<String>> dados;

public:
  ExcelExporter() {
    this->arquivo = "dados.csv";
    if (!SD.begin(SS)) {
      Serial.println("Falha ao inicializar o cartão SD!");
    }
  }

  void coletarDados() {
    float temperatura = lerSensorTemperatura();
    float umidade = lerSensorUmidade();
    String data = obterData();
    String hora = obterHora();

    // Armazena os dados coletados em um vetor
    std::vector<String> registro;
    registro.push_back(String(temperatura));
    registro.push_back(String(umidade));
    registro.push_back(dataHora);
    dados.push_back(registro);

    // Salva os dados no arquivo CSV local
    salvarDados(temperatura, umidade, dataHora);
  }

  String formatarDados() {
    String dadosCSV = "";
    for (const std::vector<String>& linha : dados) {
      for (const String& campo : linha) {
        dadosCSV += campo + ";";
      }
      dadosCSV += "\n";  // Nova linha para cada registro
    }
    return dadosCSV;
  }

  void exportarDados() {
    coletarDados();
    String dadosFormatados = formatarDados();

    // Configurar a conexão Wi-Fi
    WiFi.begin("SSID", "Senha");
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Conectando ao Wi-Fi...");
    }

    // Configurar a solicitação HTTP
    HTTPClient http;
    http.begin("http://127.0.0.1/receber_dados.php");
    http.addHeader("Content-Type", "text/csv");

    // Enviar os dados via POST
    int httpCode = http.POST(dadosFormatados);
    if (httpCode == HTTP_CODE_OK) {
      Serial.println("Dados exportados com sucesso via HTTP!");
    } else {
      Serial.println("Erro ao enviar os dados via HTTP!");
    }
    http.end();

    // Desconectar o Wi-Fi
    WiFi.disconnect(true);
  }

  void salvarDados(float temperatura, float umidade, String data, String hora) {
    File arquivoCSV = SD.open(this->arquivo, FILE_APPEND);

    if (arquivoCSV) {
      arquivoCSV.print(temperatura);
      arquivoCSV.print(";");
      arquivoCSV.print(umidade);
      arquivoCSV.print(";");
      arquivoCSV.println(data);
      arquivoCSV.print(";");
      arquivoCSV.println(data);
      arquivoCSV.close();
    } else {
      Serial.println("Erro ao abrir o arquivo CSV!");
    }
  }

  float lerSensorTemperatura() {
    // Adicionar leitura do seu sensor de temperatura
    return 25.5;  // Valor de exemplo
  }

  float lerSensorUmidade() {
    // Adicionar leitura do sensor de umidade
    return 50.0;  // Valor de exemplo
  }

  String obterData() {
    data date;
    std::ostringstream saida;
    saida << date.dataAtual();
    return saida.str();
  }

  String obterHora() {
    data date;
    std::ostringstream saida;
    saida << date.horario();
    return saida.str();
  }
};
