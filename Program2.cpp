#include <iostream>
#include <vector>
#include <fstream>
#include "Classes2.h"
#include <sstream>

double profit=0;
std::vector<Encomenda> notD;

void fillE(ifstream& dataE, std::vector<Encomenda>& p){
    int a,b,c,d;
    std::string line;
    while (std::getline(dataE, line))
    {
        std::stringstream ss(line);
        ss >> a >> b >> c >> d;
        Encomenda temp(a,b,c,d);
        p.push_back(temp);
    }
}
double efi(Encomenda a){
    return (a.getReward()/a.getTime())/a.getVol() + (a.getReward()/a.getTime())/a.getPeso();
}
//bool profitable(std::vector<Encomenda>& p, Carrinha a)
//{

//}
void orderPriority(std::vector<Encomenda>& p){
    double max=0;
    int maxP;
    int size=p.size();
    while(size>0){
        for(int i=0; i<size; i++){
            if(efi(p[i]) > max){
                max=efi(p[i]);
                maxP = i;
            }
        }
        std::swap(p[maxP], p[size-1]);
        max=0;
        maxP=-1;
        size--;
    }
}
void fillC(ifstream& dataC, std::vector<Carrinha>& c){
    int a,b,v;
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
void orderC(std::vector<Carrinha>& c)
{
    int min=1000000,minP;
    int size=c.size();
    while(size>0){
        for(int i=0; i<size; i++){
            if((c[i].getCusto()/c[i].getVolM()) + (c[i].getCusto()/c[i].getPesoM()) < min){
                min=c[i].getCusto()/c[i].getVolM() + c[i].getCusto()/c[i].getPesoM();
                minP = i;
            }
        }
        std::swap(c[minP], c[size-1]);
        min=1000000;
        minP=-1;
        size--;
    }
}
void fillV(std::vector<Carrinha>& c, std::vector<Encomenda>& p)
{
    int counter=p.size()-1;
    int i=c.size()-1;
    while(counter>=0){
        if(c[i].canAdd(p[counter])){
            c[i].addData(p[i].getVol(), p[i].getPeso(), p[i].getTime());
            p.pop_back();
            profit+=p[i].getReward();
            counter--;
        }
        else if(!c[i].canAdd(p[counter]) && c[i].hasTime()){
            c[i].resetData();
            profit-=c[i].getCusto();
        }
        else if(!c[i].hasTime()){
         i--;
        }
        else if(c[i].getVolM() < p[counter].getVol() || c[i].getPesoM() < p[counter].getPeso()){
            int j=i-1;
            while(!c[j].canAdd(p[counter]) && j>=0){
                j--;
            }
            if(j==0){
                notD.push_back(p[counter]);
                p.pop_back();
            }
            else
            {
                c[i].addData(p[i].getVol(), p[i].getPeso(), p[i].getTime());
                p.pop_back();
                profit+=p[i].getReward();
                counter--;
            }
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
    orderC(c);
    orderPriority(p);
    std::cout <<  << "\n";
    std::cout << c.size() << "\n";
    return 0;
}
