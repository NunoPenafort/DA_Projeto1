#include <iostream>
#include <vector>
#include <fstream>
#include "Classes2.h"


Encomenda::Encomenda(double volume, double peso, double reward, int time)
{
    this->volume = volume;
    this->peso   = peso;
    this->reward = reward;
    this->time   = time;
}

void Encomenda::SetValues(double volume, double peso, double reward, int time) {
    this->volume = volume;
    this->peso   = peso;
    this->reward = reward;
    this->time   = time;
}

Carrinha::Carrinha(int vol, int peso, int custo)
{
    this->volM = vol;
    this->pesoM = peso;
    this->custo = custo;
}
void Carrinha::addData(double vol, double peso,int time)
{
    volU+=vol;
    pesoU+=peso;
    this->time+=time;
}
void Carrinha::resetData(){
    this->volU  =0;
    this->pesoU =0;
}
bool Carrinha::canAdd(Encomenda a) {
    if((this->time+a.getTime()) < 864000 &&
    ((this->volU+a.getVol()) <= this->volM) &&
    ((this->pesoU+a.getPeso()) <= this->pesoM)) {return true;}
    else return false;
}
