#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "./Planet.h"
#include "./Explorer.h"

class Asteroid : public Planet {
    private:
        static int numTot;
        float damage;
    public:
        // nei metodi non serve toString perchè non aggiunge niente di nuovo rispetto al metodo di Planet
        Asteroid() noexcept;
        Asteroid(const Asteroid&) noexcept;
        void action(Explorer&) const; // throws logic_error
        ~Asteroid() noexcept;
};

#endif
