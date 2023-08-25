#include "../lib/SPI/src/SPI.h"
#include "../lib/WiFiNINA/src/WiFiNINA.h"
#include "../lib/MySQL_Connector/src/MySQL_Connection.h"
#include "../lib/MySQL_Connector/src/MySQL_Cursor.h"
#include "data.h"
#include "dht.h"

class Connection
{
private:
    // Conexão com o wifi
    #define SSID "FONMART"
    #define SSID_PASS "fmtwifi01021988/2019"
    // Conexão com o banco de dados
    #define USER_DB "estagiario_3"
    #define DB_PASS "Abc12345"

    #define pinNoteiro 8
    #define esperaLeitura 500 // TIME OUT DA LEITURA
    #define FINALIZADA true

    IPAddress *server_ip = new IPAddress(85, 10, 205, 173); // Endereço do banco
    Data *date;
    dht *sensor;
    // Comando SQL para inserir dados na tabela
    char *INSERT = "insert into arduino_fmt.registros(temperatura,umidade,data,horario) values ('%f','%f','%s','%s');";
    char *query;
    char *user = USER_DB;
    char *password = DB_PASS;

    bool sinal = HIGH;
    bool sinalAnt = HIGH;
    int valorInserido = 0;
    unsigned long controleLeitura = 0;
    int status = WL_IDLE_STATUS;

    WiFiClient cliente;
    MySQL_Connection *conexao = new MySQL_Connection((Client *)&cliente);

    bool conectaWifi()
    {
        if (WiFi.status() == WL_NO_MODULE)
        {
            return false;
            while (true)
            {
            }
        }
        String fv = WiFi.firmwareVersion();
        if (fv < "1.0.0")
        {
            Serial.println("Atualize o firmware!");
            return false;
        }
        while (status != WL_CONNECTED)
        {
            Serial.print("Tentando estabelecer conexão com: ");
            Serial.println(SSID);
            status = WiFi.begin(SSID, SSID_PASS);
            delay(10000);
        }
        Serial.println("Conectado!");
        return true;
    }

    bool enviaDados()
    {
        sprintf(query, INSERT, sensor->temperature, sensor->humidity, date->dataAtual(), date->horarioAtual());
        MySQL_Cursor *cur_mem = new MySQL_Cursor(conexao);
        cur_mem->execute(query);
        delete cur_mem;
        return true;
    }

    void leitura()
    {
        valorInserido++;
        controleLeitura = millis();
    }
    static Connection *instance;

public:
    Connection(Data *data, dht *sensor)
    {
        this->date = data;
        this->sensor = sensor;
    }

    void Connection::begin()
    {
        instance = this;
        Serial.begin(115200);
        pinMode(pinNoteiro, INPUT);
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, LOW);
        while (!Serial)
        {
        }
        conectaWifi();

        while (!conexao->connect(*server_ip, 3306, USER_DB, DB_PASS))
        {
            Serial.println("Falha na conexão com SQL");
            conexao->close();
            delay(1000);
            Serial.println("Tentando novamente...");
        }

        Serial.println("Conexão com o servidor estabelecida!");
        digitalWrite(LED_BUILTIN, HIGH);
        attachInterrupt(digitalPinToInterrupt(pinNoteiro), leituraWrapper, RISING);
    }

    void run()
    {
        if (((millis() - controleLeitura) > esperaLeitura) && (valorInserido > 0))
        {
            Serial.print("Enviando valor inserido: ");
            Serial.println(valorInserido);
            enviaDados();
            valorInserido = 0;
        }
        delay(10);
    }

    static void leituraWrapper()
    {
        instance->leitura();
    }
};