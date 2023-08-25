#include <virtuabotixRTC.h>

class Data
{
private:
#define segL 15
#define minL 24
#define horL 9
#define d_semL 5
#define d_mesL 25
#define mesL 8
#define anoL 2023

    virtuabotixRTC myRTC;
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int segundo;

public:
    Data(int clkPin, int datPin, int rstPin) : myRTC(clkPin, datPin, rstPin)
    {
        myRTC.setDS1302Time(segL, minL, horL, d_semL, d_mesL, mesL, anoL);
    }

    void atualizar()
    {
        myRTC.updateTime();

        dia = myRTC.dayofmonth;
        mes = myRTC.month;
        ano = myRTC.year;
        hora = myRTC.hours;
        minuto = myRTC.minutes;
        segundo = myRTC.seconds;
    }

    int getNumDia() const
    {
        return myRTC.dayofweek;
    }

    int getDia() const
    {
        return dia;
    }

    int getMes() const
    {
        return mes;
    }

    int getAno() const
    {
        return ano;
    }

    int getHora() const
    {
        return hora;
    }

    int getMinuto() const
    {
        return minuto;
    }

    int getSegundo() const
    {
        return segundo;
    }

    String dataAtual(){
        return String(dia) + "/" + String(mes) + "/" + String(ano);
    }

    String horarioAtual(){
        return String(hora) + ":" + String(minuto) + ":" + String(segundo);
    }
};