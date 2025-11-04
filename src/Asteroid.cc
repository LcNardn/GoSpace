#include "./headers/Asteroid.h"
#include "./headers/Planet.h"
#include "./headers/Explorer.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int Asteroid::numTot=0;

Asteroid::Asteroid() : Planet("Asteroid",numTot,AsteroidT,0) {
    numTot++;
    srand(time(NULL));
    damage = (rand()%20)+1;
    damage += (rand()%99)*0.01;
    std::cout<<"Creating asteroid: "<<*this<<std::endl;
}

Asteroid::Asteroid(const Asteroid& _o) : Planet(_o) {
    numTot++;
    damage=_o.damage;
}

void Asteroid::action(Explorer& exp) const {
    try {
        exp.damageShip(damage);
    } catch (...){
        throw;
    }

    std::cout<<"The ship has been damaged by an asteroid for "<<damage<<" health points.\nHP remaining: "<<exp.getHe()<<std::endl;
}

Asteroid::~Asteroid(){
    numTot--;
}