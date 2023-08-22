#include <Arduino.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <TimeLib.h>

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

  void limpaTela() {
    #ifdef _WIN32
      system("cls");
    #else
      std::cout << "\033[2J\033[1;1H";
    #endif
  };

  std::string horario() {
    time_t now = now();
    std::ostringstream saida;

    snprintf(saida, sizeof(9), "%02d:%02d:%02d", hour(now) - 3, minute(now), second(now));
    return saida.str();
  };
};