#include <ctime>
#include <sstream>
#include <string>

class data {
private:
  int dia;
  int mes;
  int ano;

public:
  data() {
    this->dia = 0;
    this->mes = 0;
    this->ano = 0;
  };

  int getDia() {
    return this->dia;
  };

  int getMes() {
    return this->mes;
  };

  int getAno() {
    return this->ano;
  }

  std::string dataAtual() {
    int dia, mes, ano;
    std::time_t tempo_atual = std::time(nullptr);
    std::tm *data_hora_local = std::localtime(&tempo_atual);
    this->dia = data_hora_local->tm_mday;
    this->mes = data_hora_local->tm_mon + 1;
    this->ano = data_hora_local->tm_year + 1900;

    std::ostringstream resultado;

    resultado << getDia() << "/" << getMes() << "/" << getAno();

    return resultado.str();
  };
};