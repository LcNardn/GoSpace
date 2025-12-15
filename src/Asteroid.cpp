#include "./headers/Asteroid.h"
#include "./headers/Planet.h"
#include "./headers/Explorer.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <exception>

int Asteroid::numTot=0;

Asteroid::Asteroid() noexcept : Planet("Asteroid",numTot,AsteroidT,4.0) {
    numTot++;
    srand(time(NULL));
    damage = (rand()%20)+1;
    damage += (rand()%99)*0.01;
}

Asteroid::Asteroid(const Asteroid& _o) noexcept : Planet(_o) {
    numTot++;
    damage=_o.damage;
}

void Asteroid::action(Explorer& exp) const {
    try {
        exp.damageShip(damage);
        exp.consumeEnergy(energyNeed);
        std::cout<<"The ship has been damaged by an asteroid for "<<damage<<" health points.\nHP remaining: "<<exp.getHe()<<std::endl;
    } catch (std::logic_error e){ // non ho più vita e devo segnalarlo a qualcuno
        std::cerr<<e.what()<<std::endl;
        std::cout<<"The ship doesn't have more health.\n";
        throw; // lo segnalo anche alla classe chiamante
    } catch (...){
        std::cerr<<"An unknown error has occurred.\n";
    }

}

Asteroid::~Asteroid() noexcept{
    numTot--;
}