#include <WiFi.h>
#include <HTTPClient.h>
#include <SD.h>  // Para acessar o cartão SD

class excel {
private:
  std::string arquivo;
  std::vector<std::vector<std::string>> dados;

public:
  excel() {
    this->arquivo = "dados.csv";
    // Inicialize o cartão SD
    if (!SD.begin(SS)) {
      Serial.println("Falha ao inicializar o cartão SD!");
    }
  }

  void exportaDados() {
    File arquivoCSV = SD.open(this->arquivo.c_str(), FILE_READ);

    if (arquivoCSV) {
      // Ler o conteúdo do arquivo CSV
      std::string csvContent;
      while (arquivoCSV.available()) {
        csvContent += char(arquivoCSV.read());
      }
      arquivoCSV.close();

      // Configurar a conexão Wi-Fi
      WiFi.begin("SSID", "Senha");
      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando ao Wi-Fi...");
      }

      // Configurar a solicitação HTTP
      HTTPClient http;
      http.begin("http://10.98.1.92/receber_dados.php");  // Substitua pelo endereço IP e caminho do servidor de destino
      http.addHeader("Content-Type", "text/csv");

      // Enviar o conteúdo do arquivo CSV via POST
      int httpCode = http.POST(csvContent);
      if (httpCode == HTTP_CODE_OK) {
        Serial.println("Dados exportados com sucesso!");
      } else {
        Serial.println("Erro ao enviar os dados!");
      }
      http.end();

      // Desconectar o Wi-Fi
      WiFi.disconnect(true);
    } else {
      Serial.println("Erro ao abrir o arquivo CSV!");
    }
  }
};
