#include "./headers/FirePlanet.h"
#include "./headers/EarthPlanet.h"
#include "./headers/Explorer.h"
#include "./headers/Planet.h"
#include "./headers/IndustryPlanet.h"
#include <string>
#include <iostream>
#include <exception>

int IndustryPlanet::numTot=0;

void IndustryPlanet::makeRockets(Explorer& exp) const  noexcept{
    
    objType in,out;
    if (minType == mineral_1){ // creo il razzo con il materiale che non posso prendere dal pianeta stesso
        in = mineral_2;
        out = no_Rocket;
    } else {
        in = mineral_1;
        out = rocket;
    }

    try{
        exp-=in;
        exp+=out;
        std::cout<<"You have made a rocket.\n";
    } catch (std::logic_error e){
        std::cerr<<e.what()<<std::endl;
        std::cout<<"You don't have the material to construct the rocket.\n";
    } catch (...){
        std::cerr<<"An unknown error has occurred.\n";
    }

}

IndustryPlanet::IndustryPlanet(std::string _name, float _eSup, objType _min, float _e) noexcept : Planet(_name,numTot,Industry,_e), FirePlanet(_name,_eSup,_e), EarthPlanet(_name,_min,_e){
    numTot++;
}

IndustryPlanet::IndustryPlanet(const IndustryPlanet& _o) noexcept : Planet(_o), FirePlanet(_o), EarthPlanet(_o) {
    numTot++;
}

void IndustryPlanet::action(Explorer& exp) const noexcept{

    if (!check(exp.getEn()-energySup)) return;

    makeRockets(exp);
    cooking(exp);
    mining(exp);

    exp.consumeEnergy(energyNeed+energySup);

}

std::string IndustryPlanet::toString() const  noexcept{
    return FirePlanet::toString() + " " + ((minType == mineral_2) ? "mineral_2" : "mineral_1");
}

IndustryPlanet::~IndustryPlanet() noexcept{
    numTot--;
}