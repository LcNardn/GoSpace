#include "./headers/Planet.h"
#include "./headers/Explorer.h"
#include "./headers/FirePlanet.h"
#include <string>
#include <iostream>
#include <exception>

int FirePlanet::numTot=0;

FirePlanet::FirePlanet(std::string _name,float _es,float _e) : Planet(_name,numTot,Fire,_e), energySup(_es){
    numTot++;
    std::cout<<"Created FirePlanet: "<<*this<<std::endl;
}

FirePlanet::FirePlanet(const FirePlanet& _o) : Planet(_o), energySup(_o.energySup) {
    numTot++;
}

void FirePlanet::cooking(Explorer& exp) const{
    try {
        exp-=fish;
        exp+=food;
        std::cout<<"You have cooked a fish!\n";
    } catch (std::logic_error e) {
        std::cerr<<e.what()<<std::endl;
        std::cout<<"You can't cook a fish that you don't have.\n";
    } catch (...){
        std::cerr<<"An unknown error has occured.\n";
    }
}

void FirePlanet::action(Explorer& exp) const{

    if(!check(exp.getEn()-energySup)) return; // energyNeed + energySup < exp.getEn() <=> energyNeed < exp.getEn() - energySup

    cooking(exp);

    exp.consumeEnergy(energyNeed+energySup);
    
}

std::string FirePlanet::toString() const{
    return Planet::toString() + " " + std::to_string(energySup);
}

FirePlanet::~FirePlanet(){ numTot--; }