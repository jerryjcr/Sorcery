#ifndef CONCRETERITUALS_H_
#define CONCRETERITUALS_H_
#include "Ritual.h"

class DarkRitual : public Ritual {
    public:
        DarkRitual();
        ~DarkRitual() = default;
};

class AuraOfPower : public Ritual {
    public:
        AuraOfPower();
        ~AuraOfPower() = default;
};

class Standstill : public Ritual {
    public:
        Standstill();
        ~Standstill() = default;
};

#endif