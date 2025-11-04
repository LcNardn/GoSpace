#ifndef __EXPLORER_H__
#define __EXPLORER_H__

#include <iostream>
#include <unordered_map>

typedef enum{
    fish,food,rocket,no_Rocket,mineral_1,mineral_2
} objType;

class Explorer{
    private:

        // limiti
        static const int oxInit;
        static const float enInit;
        static const float heInit;
        static const int maxCapacity;

        // statistiche
        int oxygen;
        float energy;
        float health;
        std::unordered_map<objType,int> inventory;

    public:

        // costruttori
        Explorer();
        Explorer(const Explorer&);

        // getters
        int getOx() const;
        float getEn() const;
        float getHe() const;

        // inventario
        Explorer& operator+=(objType);
        Explorer& operator-=(objType); // throws logic_error
        bool shootRocket();

        // health
        void damageShip(float); // throws logic_error
        bool repairShip();

        // energy
        void rest();
        void consumeEnergy(float);

        // oxygen
        Explorer operator++();
        Explorer operator--(); // throws logic_error

        friend std::ostream& operator<<(std::ostream&,const Explorer&);

        ~Explorer();
};

std::ostream& operator<<(std::ostream&,const Explorer&);

#endif
