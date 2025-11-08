#ifndef __PLANET_H__
#define __PLANET_H__

#include "./Explorer.h"
#include <string>
#include <iostream>

typedef enum {
    Water, Fire, Earth, Steam, Industry, Destroyed, AsteroidT
} pType;

class Planet{

    private:
        const std::string name;
        const std::pair<pType,int> id;
        const pType type;
        
    protected:
        bool isDestroyed;
        const float energyNeed;
        //costruttori
        Planet()=delete; // non posso creare un pianeta senza niente
        Planet(std::string,int,pType,float);
        Planet(const Planet&);

        // funzione di controllo
        inline bool check(float) const;

    public:
        // per gestire la disrtuzione
        bool destroy();
        bool regenerate(Explorer&);

        // le azioni specifiche dei pianeti vengono invocate con action
        virtual void action(Explorer&) const = 0;

        // per la stampa
        friend std::ostream& operator<<(std::ostream&,const Planet&);

        // distruttore
        virtual ~Planet();
};

std::ostream& operator<<(std::ostream&,const Planet&);

#endif
