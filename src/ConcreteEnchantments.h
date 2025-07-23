#ifndef CONCRETEENCHANTMENTS_H_
#define CONCRETEENCHANTMENTS_H_

#include "Enchantment.h"

class GiantStrength : public Enchantment {
    public:
        GiantStrength(std::unique_ptr<Minion> parent);
        ~GiantStrength() = default;
};

class Enrage : public Enchantment {
    public:
        Enrage(std::unique_ptr<Minion> parent);
        ~Enrage() = default;
};

class Haste : public Enchantment {
    public:
        Haste(std::unique_ptr<Minion> parent);
        ~Haste() = default;
};

class MagicFatigue : public Enchantment {
    public:
        MagicFatigue(std::unique_ptr<Minion> parent);
        ~MagicFatigue() = default;
};

class Silence : public Enchantment {
    public:
        Silence(std::unique_ptr<Minion> parent);
        ~Silence() = default;
};

#endif