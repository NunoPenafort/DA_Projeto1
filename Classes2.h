#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#ifndef Classes2_h
#define Classes2_h
class Encomenda
{
private:
    double volume;
    double peso;
    double reward;
    int time;
public:
    Encomenda(double volume, double peso, double reward, int time);

    void SetValues(double volume, double peso, double reward, int time);

    double getVol() {return volume;}
    double getPeso() {return peso;}
    double getReward() {return reward;}
    int getTime() {return time;}

};
class Carrinha
{
private:
    double volM;
    double volU=0;
    double pesoM;
    double pesoU=0;
    int time=0;
    double custo;
public:
    Carrinha(int vol, int peso, int custo);

    void addData(double vol, double peso, int time);
    void resetData();

    bool canAdd(Encomenda a);
    bool hasTime(){return (time<864000);}

    double getVolM() const{return volM;}
    double getVolU(){return volU;}
    double getPesoM() const{return pesoM;}
    double getPesoU(){return pesoU;}
    double getCusto(){return custo;}

};

#endif
