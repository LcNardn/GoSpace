#include "./headers/Planet.h"
#include "./headers/Explorer.h"
#include <string>
#include <iostream>

Planet::Planet(std::string _name, int _n, pType _t, float _energy) noexcept : name(_name), type(_t), id({_t,_n}), energyNeed(_energy) {
    isDestroyed = (_t==Destroyed);
}

Planet::Planet(const Planet& _o) noexcept : name(_o.name), type(_o.type), id(_o.id), energyNeed(_o.energyNeed) {
    isDestroyed = _o.isDestroyed;
}

bool Planet::check(float energyExp) const noexcept{
    if (isDestroyed) { // non posso fare niente se il pianeta è distrutto o non ho energia a sufficienza
        std::cerr<<"Any action on "<<*this<<" cannot be done.\n";
        std::cout<<"The planet is destroyed. You need to regenerate it first.\n";
        return false;
    } else if (energyExp<energyNeed) {
        std::cerr<<"The action on "<<*this<<" cannot be done due to low energy.\n";
        std::cout<<"You are too tired. You need to rest fisrt.\n";
        return false;
    } else return true;
}

bool Planet::destroy() noexcept{
    if (!isDestroyed){
        isDestroyed=true;
        return true;
    } else return false;
}

bool Planet::regenerate(Explorer& exp) noexcept{
    if (isDestroyed && type!=Destroyed){
        try {
            exp-=no_Rocket;
            isDestroyed=false;
            return true;
        } catch (std::logic_error e) {
            std::cerr<<e.what()<<std::endl;
        } catch (...){
            std::cerr<<"An unknown error has occurred.\n";
        }
        return false;
    } else return false;
}

std::string Planet::toString() const  noexcept{
    std::string typeS;
    switch (type){
        case Water: typeS.assign("W"); break;
        case Fire: typeS.assign("F"); break;
        case Earth: typeS.assign("E"); break;
        case Steam: typeS.assign("S"); break;
        case Industry: typeS.assign("I"); break;
        case Destroyed: typeS.assign("D"); break;
        case AsteroidT: typeS.assign("A"); break;
        default: typeS.assign("U"); break;
    }

    if (isDestroyed){ // se salvo mentre un pianeta è distrutto, lo segalo
        typeS.append(" d");
    } else { // altrimenti uso un carattere per rendere uniforme le linee
        typeS.append(" i");
    }

    return typeS + " " + name + " " + std::to_string(energyNeed);
}

Planet::~Planet() noexcept{  }

std::ostream& operator<<(std::ostream& out,const Planet& p){
    out<<"Planet: "<<p.name<<" (";
    switch (p.type){
        case Water: out<<"Wa"; break;
        case Fire: out<<"Fi"; break;
        case Earth: out<<"Ea"; break;
        case Steam: out<<"St"; break;
        case Industry: out<<"In"; break;
        case Destroyed: out<<"De"; break;
        case AsteroidT: out<<"As"; break;
        default: out<<"Unkown"; break;
    }
    out<<","<<p.id.second<<") Currently"<<(p.isDestroyed ? " " : " not ")<<"destoyed.";
    return out;
}