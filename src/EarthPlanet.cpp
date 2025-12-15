#include "./headers/EarthPlanet.h"
#include "./headers/Planet.h"
#include "./headers/Explorer.h"
#include <string>
#include <iostream>

int EarthPlanet::numTot=0;

objType EarthPlanet::chooseMineral(objType obj) noexcept {
    return ((obj != mineral_1 && obj != mineral_2) ? mineral_1 : obj);
}

EarthPlanet::EarthPlanet(std::string _name, objType _mineral, float _energy) noexcept : Planet(_name,numTot,Earth,_energy), minType(chooseMineral(_mineral)){
    numTot++;
}

EarthPlanet::EarthPlanet(const EarthPlanet& _o) noexcept : Planet(_o), minType(_o.minType){
    numTot++;
}

void EarthPlanet::mining(Explorer& exp) const noexcept {

    exp+=minType;
    std::cout<<"You have mined a mineral!\n";

}

void EarthPlanet::action(Explorer& exp) const noexcept {

    if(!check(exp.getEn())) return;

    mining(exp);

    exp.consumeEnergy(energyNeed);

    
}

std::string EarthPlanet::toString() const noexcept {
    return Planet::toString() + " " + (minType == mineral_1 ? "mineral_1" : "mineral_2");
}

EarthPlanet::~EarthPlanet() noexcept { numTot--; }