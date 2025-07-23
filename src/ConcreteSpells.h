#ifndef CONCRETESPELLS_H_
#define CONCRETESPELLS_H_

#include "Spell.h"

class Banish : public Spell {
    public:
        Banish();
        virtual ~Banish() = default;
};

class Unsummon : public Spell {
    public:
        Unsummon();
        virtual ~Unsummon() = default;
};

class Recharge : public Spell {
    public:
        Recharge();
        virtual ~Recharge() = default;
};

class Disenchant : public Spell {
    public:
        Disenchant();
        virtual ~Disenchant() = default;
};

class RaiseDead : public Spell {
    public:
        RaiseDead();
        virtual ~RaiseDead() = default;
};

class Blizzard : public Spell {
    public:
        Blizzard();
        virtual ~Blizzard() = default;
};

#endif
