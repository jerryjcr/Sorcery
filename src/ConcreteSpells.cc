#include "ConcreteSpells.h"

#include "ConcreteAbilities.h"

Banish::Banish() : Spell{"Banish", 2, std::make_unique<BanishAbility>(0)} {}

Unsummon::Unsummon()
    : Spell{"Unsummon", 1, std::make_unique<UnsummonAbility>(0)} {}

Recharge::Recharge()
    : Spell{"Recharge", 1, std::make_unique<RechargeAbility>(0)} {}

Disenchant::Disenchant()
    : Spell{"Disenchant", 1, std::make_unique<DisenchantAbility>(0)} {}

RaiseDead::RaiseDead()
    : Spell{"RaiseDead", 1, std::make_unique<RaiseDeadAbility>(0)} {}

Blizzard::Blizzard()
    : Spell{"Blizzard", 1, std::make_unique<BlizzardAbility>(0)} {}
