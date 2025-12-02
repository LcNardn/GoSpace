#ifndef __GALAXY_H__
#define __GALAXY_H__

#include "./PlanetInclude.h"
#include "./Graph.h"
#include "./Explorer.h"

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>

class Galaxy {
    private:
        int currentPlanet;
        const std::string saveFile;
        std::unique_ptr<Explorer> exp; // impongo che exp sia unico per ogni galassia
        Graph<Planet*> map;

    public:
        // costruttori
        Galaxy()=delete;
        Galaxy(std::fstream&,std::string,std::unique_ptr<Explorer>&,int=0); // throws domain_error
        Galaxy(const Galaxy&);
        Galaxy& operator=(const Galaxy&);
        
        // move semantics visto che gestisco risorse dinamiche
        Galaxy(Galaxy&&);
        Galaxy& operator=(Galaxy&&);

        // metodi per gli asteroidi
        void spawnAsteroid();
        void destroyAsteroid();

        // per gestire l'esplorazione
        void beginTurn(); // throws logic_error
        void action() const;
        void regenerate() const;
        void travel(); // throws logic_error

        // stampa i pianeti adiacenti
        friend std::ostream& operator<<(std::ostream&,const Galaxy&);

        // distruttore
        ~Galaxy();
};

std::ostream& operator<<(std::ostream&,const Galaxy&);

#endif
