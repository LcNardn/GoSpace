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
        std::weak_ptr<Planet> destroyedPlanet;

    public:
        // costruttori
        Galaxy()=delete;
        Galaxy(std::fstream&,std::string,std::unique_ptr<Explorer>&,std::weak_ptr<Planet>); // throws domain_error
        Galaxy(const Galaxy&) noexcept;
        Galaxy& operator=(const Galaxy&) noexcept;
        
        // move semantics visto che gestisco risorse dinamiche
        Galaxy(Galaxy&&) noexcept;
        Galaxy& operator=(Galaxy&&) noexcept;

        // metodi per gli asteroidi
        void spawnAsteroid() noexcept;
        void destroyAsteroid() noexcept;

        // per gestire l'esplorazione
        void beginTurn(); // throws logic_error
        void action() const noexcept;
        void regenerate() const noexcept;
        void travel(); // throws logic_error
        void repair() noexcept;

        // stampa i pianeti adiacenti
        friend std::ostream& operator<<(std::ostream&,const Galaxy&);

        // distruttore
        ~Galaxy() noexcept;
};

std::ostream& operator<<(std::ostream&,const Galaxy&);

#endif
