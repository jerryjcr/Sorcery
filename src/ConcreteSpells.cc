#include "ConcreteSpell.h"
#include "ConcreteAbilities.h"

Banish::Banish() : Spell{"Banish", 2, std::make_unique<BanishAbility>()} {}

Unsummon::Unsummon() : Spell{"Unsummon", 1, std::make_unique<UnsummonAbility>()} {}

Recharge::Recharge() : Spell{"Recharge", 1, std::make_unique<RechargeAbility>()} {}

Disenchant::Disenchant() : Spell{"Disenchant", 1, std::make_unique<DisenchantAbility>()} {}

RaiseDead::RaiseDead() : Spell{"RaiseDead", 1, std::make_unique<RaiseDeadAbility>()} {}

Blizzard::Blizzard() : Spell{"Blizzard", 1, std::make_unique<BlizzardAbility>()} {}
