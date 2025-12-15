#include "./headers/Planet.h"
#include "./headers/Explorer.h"
#include "./headers/DestroyedPlanet.h"
#include <string>
#include <iostream>

DestroyedPlanet::DestroyedPlanet() noexcept : Planet("Destroyed",0,Destroyed,0.0){
    
}

void DestroyedPlanet::action(Explorer& exp) const noexcept  {
    if (!check(exp.getEn())) return; // entrerà sempre dentro l'if
}

DestroyedPlanet::~DestroyedPlanet() noexcept {
    
}