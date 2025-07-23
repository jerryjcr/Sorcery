#include "ConcreteRituals.h"

#include "ConcreteAbilities.h"

DarkRitual::DarkRitual()
    : Ritual{"Dark Ritual", 0, 5, 1, std::make_unique<DarkRitualAbility>(0)} {}

AuraOfPower::AuraOfPower()
    : Ritual{"Aura Of Power", 0, 5, 1,
             std::make_unique<AuraOfPowerAbility>(0)} {}

Standstill::Standstill()
    : Ritual{"Standstill", 0, 5, 1, std::make_unique<StandstillAbility>(0)} {}
