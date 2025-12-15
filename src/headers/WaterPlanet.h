#ifndef __WATERPLANET_H__
#define __WATERPLANET_H__

#include "./Planet.h"
#include "./Explorer.h"
#include <string>

class WaterPlanet : virtual public Planet{
    private:
        static int numTot;
        const int qFish;
    
    protected:
        void fishing(Explorer&) const noexcept;

    public:
        WaterPlanet()=delete;
        WaterPlanet(std::string,int,float) noexcept;
        WaterPlanet(const WaterPlanet&) noexcept;
        void action(Explorer&) const noexcept;
        std::string toString() const noexcept;
        ~WaterPlanet();
};

#endif
