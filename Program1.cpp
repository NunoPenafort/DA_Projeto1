#include <iostream>
#include <vector>
#include <fstream>
#include "Classes2.h"
#include <sstream>

int timeleft=864000;
int usedVans=0;
void fillE(ifstream& dataE, std::vector<Encomenda>& p){
    double a,b,c;
    int d;
    std::string line;
    while (std::getline(dataE, line))
    {
        std::stringstream ss(line);
        ss >> a >> b >> c >> d;
        Encomenda temp(a,b,c,d);
        p.push_back(temp);
    }
}
void fillC(ifstream& dataC, std::vector<Carrinha>& c){
    double a,b,v;
    std::string line;
    std::getline(dataC,line);
    while (std::getline(dataC, line))
    {
        std::stringstream ss(line);
        ss >> a >> b >> v;
        Carrinha temp(a,b,v);
        c.push_back(temp);
    }
}
void fillVans(std::vector<Carrinha>& c, std::vector<Encomenda>& p)
{
    int counter=p.size()-1;
    for(int i=c.size(); i>0; i--){
        while(c[i].canAdd(p[counter]) && counter>=0){
            timeleft-=p[counter].getTime();
            c[i].addData(p[counter].getVol(),p[counter].getPeso(),0);
            p.pop_back();
            counter--;
        }
        c.pop_back();
        usedVans++;
        if(p.size()==0){break;}
    }
}
void orderV(std::vector<Carrinha>& c){
    double max=0,maxP;
    int size=c.size();
    while(size>0){
        for(int i=0; i<size; i++){
            if((c[i].getVolM()+c[i].getPesoM()) > max){
                max=c[i].getVolM()+c[i].getPesoM();
                maxP=i;
            }
            std::swap(c[maxP], c[size-1]);
            max=0;
            maxP=-1;
            size--;
        }
    }
}
void orderD(std::vector<Encomenda>& p){
    int max=0,maxP;
    int size=p.size();
    while(size>0){
        for(int i=0; i<size; i++){
            if((p[i].getVol()+p[i].getPeso()) > max){
                max=p[i].getVol()+p[i].getPeso();
                maxP=i;
            }
            std::swap(p[maxP], p[size-1]);
            max=0;
            maxP=-1;
            size--;
        }
    }
}
int main() {
    std::vector<Encomenda> p;
    std::vector<Carrinha> c;
    std::ifstream dataE;
    std::ifstream dataC;
    dataE.open("encomendas.txt", ios::in);
    if(!dataE.is_open()) {
        std::cout << "Could not open the file ! \n";
    }
    dataC.open("carrinhas.txt", ios::in);
    if(!dataC.is_open()) {
        std::cout << "Could not open the file ! \n";
    }
    fillE(dataE, p);
    fillC(dataC, c);
    orderV(c);
    orderD(p);
    fillVans(c,p);
    if(timeleft<=0){
        std::cout << "Not able to deliver all deliveries\n";
    }
    else
    std::cout << "Vans used: " << usedVans << "\n" << "Time left: " << timeleft << "\n";
    std::cout << "Deliveries left: " << p.size() << "\n";
    return 0;
}
