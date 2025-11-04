#include "./headers/SteamPlanet.h"
#include "./headers/FirePlanet.h"
#include "./headers/WaterPlanet.h"
#include "./headers/Planet.h"
#include "./headers/Explorer.h"
#include <string>
#include <iostream>
 
int SteamPlanet::numTot=0;

void SteamPlanet::replentishO(Explorer& exp) const{
    for (int i=0;i<capacityO;i++){
        ++exp;
    }
}

SteamPlanet::SteamPlanet(std::string _name, int _qFish, float _e, float _eSup,int _O2) : Planet(_name,numTot,Steam,_e), WaterPlanet(_name,_qFish,_e), FirePlanet(_name,_eSup,_e), capacityO(_O2) {
    numTot++;
    std::cout<<"Creating SteamPlanet: "<<*this<<std::endl;
}

SteamPlanet::SteamPlanet(const SteamPlanet& _o) : Planet(_o), WaterPlanet(_o), FirePlanet(_o), capacityO(_o.capacityO){
    numTot++;
}

void SteamPlanet::action(Explorer& exp) const{

    if(!check(exp.getEn()-energySup)) return;

    replentishO(exp);
    fishing(exp); // meglio chiamare prima fishing e poi cooking
    cooking(exp); // così ho almeno un pesce da cucinare

    exp.consumeEnergy(energyNeed);

}

SteamPlanet::~SteamPlanet(){
    numTot--;
}