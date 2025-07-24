#include "ConcreteSpells.h"

#include "ConcreteAbilities.h"

Banish::Banish() : Spell{"Banish", 2, std::make_unique<BanishAbility>(0)} {}

const std::vector<std::string> Banish::getDescription() const {
  return std::vector<std::string>{" Destroy target minion or", " ritual", ""};
}

Unsummon::Unsummon()
    : Spell{"Unsummon", 1, std::make_unique<UnsummonAbility>(0)} {}
const std::vector<std::string> Unsummon::getDescription() const {
  return std::vector<std::string>{" Return target minion to its",
                                  " player's hand", ""};
}

Recharge::Recharge()
    : Spell{"Recharge", 1, std::make_unique<RechargeAbility>(0)} {}

const std::vector<std::string> Recharge::getDescription() const {
  return std::vector<std::string>{" Your ritual gains 3 charges", "", ""};
}

Disenchant::Disenchant()
    : Spell{"Disenchant", 1, std::make_unique<DisenchantAbility>(0)} {}

const std::vector<std::string> Disenchant::getDescription() const {
  return std::vector<std::string>{" Destroy the top enchantment",
                                  " on target minion", ""};
}

RaiseDead::RaiseDead()
    : Spell{"Raise Dead", 1, std::make_unique<RaiseDeadAbility>(0)} {}

const std::vector<std::string> RaiseDead::getDescription() const {
  return std::vector<std::string>{" Resurrect the top minion in",
                                  " your graveyard and set its",
                                  " defence to 1"};
}

Blizzard::Blizzard()
    : Spell{"Blizzard", 1, std::make_unique<BlizzardAbility>(0)} {}

const std::vector<std::string> Blizzard::getDescription() const {
  return std::vector<std::string>{" Deal 2 damage to all minions",
                                  "", ""};
}
