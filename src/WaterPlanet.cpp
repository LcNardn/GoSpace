#include "./headers/Planet.h"
#include "./headers/Explorer.h"
#include "./headers/WaterPlanet.h"
#include <string>
#include <iostream>

int WaterPlanet::numTot = 0;

WaterPlanet::WaterPlanet(std::string _name, int _q, float _e) noexcept : Planet(_name,numTot,Water,_e), qFish(_q){
    numTot++;
}

WaterPlanet::WaterPlanet(const WaterPlanet& _o) noexcept : Planet(_o), qFish(_o.qFish){
    numTot++;
}

void WaterPlanet::fishing(Explorer& exp) const noexcept{
    
    for(int i=0;i<qFish;i++){
        exp+=fish;
    }

    std::cout<<"You have caught "<<qFish<<" fishe(s)!\n";
}

void WaterPlanet::action(Explorer& exp) const noexcept{
    
    if(!check(exp.getEn())) return;

    fishing(exp);

    exp.consumeEnergy(energyNeed);
    
}

std::string WaterPlanet::toString() const noexcept {
    return Planet::toString() + " " + std::to_string(qFish);
}

WaterPlanet::~WaterPlanet() noexcept{ numTot--; }