#include "./headers/EarthPlanet.h"
#include "./headers/Planet.h"
#include "./headers/Explorer.h"
#include <string>
#include <iostream>

int EarthPlanet::numTot=0;

objType EarthPlanet::chooseMineral(objType obj){
    return ((obj != mineral_1 && obj != mineral_2) ? mineral_1 : obj);
}

EarthPlanet::EarthPlanet(std::string _name, objType _mineral, float _energy) : Planet(_name,numTot,Earth,_energy), minType(chooseMineral(_mineral)){
    numTot++;
}

EarthPlanet::EarthPlanet(const EarthPlanet& _o) : Planet(_o), minType(_o.minType){
    numTot++;
}

void EarthPlanet::mining(Explorer& exp) const{

    exp+=minType;
    std::cout<<"You have mined a mineral!\n";

}

void EarthPlanet::action(Explorer& exp) const{

    if(!check(exp.getEn())) return;

    mining(exp);

    exp.consumeEnergy(energyNeed);

    
}

std::string EarthPlanet::toString() const {
    return Planet::toString() + " " + (minType == mineral_1 ? "mineral_1" : "mineral_2");
}

EarthPlanet::~EarthPlanet(){ numTot--; }