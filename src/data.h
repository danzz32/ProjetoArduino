#include <Arduino.h>
#include <time.h>

class data
{
private:
    int ano;
    int mes;
    int dia;
    int hora;
    int minuto;
    int segundo;

public:
    data()
    {
        syncTime();
    }

    bool syncTime()
    {
        time_t atual;
        time(&atual);
        struct tm *info = localtime(&atual);
        this->dia = info->tm_mday;
        this->mes = info->tm_mon + 1;
        this->ano = info->tm_year + 1900;
        this->hora = info->tm_hour;
        this->minuto = info->tm_min;
        this->segundo = info->tm_sec;
        return true;
    }

    int getHora()
    {
        return this->hora;
    }

    int getMin()
    {
        return this->minuto;
    }

    int getSec()
    {
        return this->segundo;
    }

    int getAno()
    {
        return this->ano;
    }

    int getMes()
    {
        return this->mes;
    }

    int getDia()
    {
        return this->dia;
    }
};
