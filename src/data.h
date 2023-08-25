#include "../lib/Time/TimeLib.h"

class data {
private:
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int segundo;

public:
    // Construtor que obtém a data e hora atual do sistema
    data() {
        // Obtenha a hora atual do sistema
        time_t tempoAtual = now();

        // Converta a hora atual em uma estrutura tm
        tmElements_t tempoElementos;
        breakTime(tempoAtual, tempoElementos);

        dia = tempoElementos.Day;
        mes = tempoElementos.Month;
        ano = tempoElementos.Year + 1970; // O ano começa em 1970
        hora = tempoElementos.Hour;
        minuto = tempoElementos.Minute;
        segundo = tempoElementos.Second;
    }

    // Métodos para obter o dia, mês, ano, hora, minuto e segundo
    int getDia() const {
        return dia;
    }

    int getMes() const {
        return mes;
    }

    int getAno() const {
        return ano;
    }

    int getHora() const {
        return hora;
    }

    int getMinuto() const {
        return minuto;
    }

    int getSegundo() const {
        return segundo;
    }
};
