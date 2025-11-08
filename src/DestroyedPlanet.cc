#include "./headers/Planet.h"
#include "./headers/Explorer.h"
#include "./headers/DestroyedPlanet.h"
#include <string>
#include <iostream>

int DestroyedPlanet::numTot=0;

DestroyedPlanet::DestroyedPlanet() : Planet("Cad",numTot,Destroyed,0.0){
    numTot++;
}

void DestroyedPlanet::action(Explorer& exp) const{
    if (!check(exp.getEn())) return; // entrerà sempre dentro l'if
}

DestroyedPlanet::~DestroyedPlanet(){
    numTot--;
}