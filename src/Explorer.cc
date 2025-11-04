#include "./headers/Explorer.h"
#include <exception>

#define DELTA 0.000001

const int Explorer::oxInit=10;
const float Explorer::enInit=10.0;
const float Explorer::heInit=100.0;
const int Explorer::maxCapacity=5;

// costruttori
Explorer::Explorer(){
    oxygen=oxInit;
    energy=enInit;
    health=heInit;
}

Explorer::Explorer(const Explorer& o) : inventory(o.inventory) {
    oxygen=o.oxygen;
    energy=o.energy;
    health=o.health;
}

// getters
int Explorer::getOx() const{ return oxygen; }

float Explorer::getEn() const{ return energy; }

float Explorer::getHe() const{ return health; }


// inventario
Explorer& Explorer::operator+=(objType obj){
    if (inventory[obj] < maxCapacity ){
        inventory[obj]++;
    }
    return *this;
}

Explorer& Explorer::operator-=(objType obj){
    if (inventory[obj] > 0 ){
        inventory[obj]--;
    } else throw std::logic_error("No item in inventory");
    return *this;
}

bool Explorer::shootRocket(){
    if (inventory[rocket] > 0){
        *this-=rocket;
        return true;
    } else return false;
}

// health
void Explorer::damageShip(float dmg){
    health-=dmg;
    if (health <= 0) throw std::logic_error("No more health");
}

bool Explorer::repairShip(){
    while(inventory[mineral_2]>0 && (heInit-health) > DELTA && energy>0){
        health+=((heInit-health)*0.5); // cura 20% dei danni subiti
        *this-=mineral_2;
    }
    consumeEnergy(3);
    return true;
}

// energy
void Explorer::rest(){

    if ( (energy-enInit) > DELTA ) return;

    energy+=3;
    if (inventory[food] > 0){
        *this-=food;
        energy+=3;
    }
}

void Explorer::consumeEnergy(float en){
    energy-=en;
    if (energy < 0.0) energy=0.0;
}

// oxygen
Explorer Explorer::operator++(){
    oxygen = (oxygen+1 > oxInit ? oxInit : oxygen+1);
    return *this;
}

Explorer Explorer::operator--(){
    oxygen--;
    if (oxygen==0) throw std::logic_error("No more oxygen");
    return *this;
}

Explorer::~Explorer(){  }

std::ostream& operator<<(std::ostream& out, const Explorer& ex){
    out<<"Explorer:\n\tShip health: "<<ex.health<<"\n\tEnergy: "<<ex.energy<<"\n\tOxygen: "<<ex.oxygen;
    out<<"\n\tInventory:";
    for (std::pair<objType,int> i : ex.inventory){
        out<<"\n\t\t";
        switch (i.first){
            case fish: out<<"Fish: "; break;
            case food: out<<"Food: "; break;
            case rocket: out<<"Rockets: "; break;
            case no_Rocket: out<<"Anti-rocket: "; break;
            case mineral_1: out<<"1-Mineral: "; break;
            case mineral_2: out<<"2-Mineral: "; break;
        
            default: out<<"Other: "; break;
        }
        out<<i.second;
    }
    return out;
}