#include "ConcreteRituals.h"

#include "ConcreteAbilities.h"



DarkRitual::DarkRitual()
    : Ritual{"Dark Ritual", 0, 5, 1, std::make_unique<DarkRitualAbility>(0)} {}
const std::vector<std::string> DarkRitual::getDescription() const {
  return std::vector<std::string>{" 1   | At the start of your",
                                  "------ turn, gain 1 magic ", ""};
}

AuraOfPower::AuraOfPower()
    : Ritual{"Aura Of Power", 0, 5, 1,
             std::make_unique<AuraOfPowerAbility>(0)} {}
const std::vector<std::string> AuraOfPower::getDescription() const {
  return std::vector<std::string>{" 1   | Whenever a minion enters",
                                  "------ play under your control,", "       it gains +1/+1 "};
}

Standstill::Standstill()
    : Ritual{"Standstill", 0, 5, 1, std::make_unique<StandstillAbility>(0)} {}
const std::vector<std::string> Standstill::getDescription() const {
  return std::vector<std::string>{" 2   | Whenever a minion",
                                  "------ enters play, destroy it.", ""};
}
