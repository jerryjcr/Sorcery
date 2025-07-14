#ifndef ENCHANTMENTS_H_
#define ENCHANTMENTS_H_

#include "abstractCard.h"
#include "minions.h"

class Enchantment : public Minion {
    protected:
        std::shared_ptr<Minion> parent;
    public:
        Enchantment(std::shared_ptr<Minion> parent);
};

class GiantStrength : public Enchantment {
    public:
        GiantStrength(std::shared_ptr<Minion> parent);
        virtual int getDefense() const override;
        virtual int getAttack() const override;
};

#endif