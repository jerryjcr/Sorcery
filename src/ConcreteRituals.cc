#include "ConcreteRituals.h"
#include "ConcreteAbilities.h"

DarkRitual::DarkRitual() : Ritual{"Dark Ritual", 0, 5, 1, std::make_unique<DarkRitualAbility>()} {}

AuraOfPower::AuraOfPower() : Ritual{"Aura Of Power", 0, 5, 1, std::make_unique<AuraOfPowerAbility>()} {}

Standstill::Standstill() : Ritual{"Standstill", 0, 5, 1, std::make_unique<StandstillAbility>()} {}
