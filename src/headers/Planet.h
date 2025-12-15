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
        Planet(std::string,int,pType,float) noexcept;
        Planet(const Planet&) noexcept;

        // funzione di controllo
        bool check(float) const noexcept;

    public:
        // per gestire la disrtuzione
        bool destroy() noexcept;
        bool regenerate(Explorer&) noexcept;

        // getter
        inline pType getType() const noexcept {return type;}

        // le azioni specifiche dei pianeti vengono invocate con action
        virtual void action(Explorer&) const = 0;

        // per la stampa
        friend std::ostream& operator<<(std::ostream&,const Planet&);
        virtual std::string toString() const noexcept;

        // distruttore
        virtual ~Planet() noexcept;
};

std::ostream& operator<<(std::ostream&,const Planet&);

#endif
