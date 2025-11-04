#include "./headers/Planet.h"
#include "./headers/Explorer.h"
#include "./headers/WaterPlanet.h"
#include <string>
#include <iostream>

int WaterPlanet::numTot = 0;

WaterPlanet::WaterPlanet(std::string _name, int _q, float _e) : Planet(_name,numTot,Water,_e), qFish(_q){
    numTot++;
    std::cout<<"Created WaterPlanet: "<<*this<<std::endl;
}

WaterPlanet::WaterPlanet(const WaterPlanet& _o) : Planet(_o), qFish(_o.qFish){
    numTot++;
}

void WaterPlanet::fishing(Explorer& exp) const{
    
    for(int i=0;i<qFish;i++){
        exp+=fish;
    }

    std::cout<<"You have caught "<<qFish<<" fishe(s)!\n";
}

void WaterPlanet::action(Explorer& exp) const{
    
    if(!check(exp.getEn())) return;

    fishing(exp);

    exp.consumeEnergy(energyNeed);
    
}

WaterPlanet::~WaterPlanet(){ numTot--; }