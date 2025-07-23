#include "ConcreteEnchantments.h"

#include <iostream>

GiantStrength::GiantStrength(std::unique_ptr<Minion> parent)
    : Enchantment{"Giant Strength", 1, std::move(parent)} {}

const std::vector<std::string> GiantStrength::getDescription() const {
  return std::vector<std::string>{"", "", ""};
}

int GiantStrength::getAttack() const { return parent->getAttack() + 2; }

int GiantStrength::getDefence() const { return parent->getDefence() + 2; }

Enrage::Enrage(std::unique_ptr<Minion> parent)
    : Enchantment{"Enrage", 1, std::move(parent)} {}

const std::vector<std::string> Enrage::getDescription() const {
  return std::vector<std::string>{"", "", ""};
}

int Enrage::getAttack() const { return parent->getAttack() * 2; }

int Enrage::getDefence() const { return parent->getDefence() * 2; }

Haste::Haste(std::unique_ptr<Minion> parent)
    : Enchantment{"Haste", 1, std::move(parent)} {}

const std::vector<std::string> Haste::getDescription() const {
  return std::vector<std::string>{"Enchanted minion gains +1",
                                  "actions each turn.", ""};
}

int Haste::getActions() const { return parent->getActions() + 1; }

MagicFatigue::MagicFatigue(std::unique_ptr<Minion> parent)
    : Enchantment{"Magic Fatigue", 1, std::move(parent)} {}

const std::vector<std::string> MagicFatigue::getDescription() const {
  return std::vector<std::string>{"Enchanted minion's activated",
                                  "ability costs 2 more", ""};
}

int MagicFatigue::getAbilityCost() const {
  return parent->getAbilityCost() + 2;
}

Silence::Silence(std::unique_ptr<Minion> parent)
    : Enchantment{"Silence", 1, std::move(parent)} {}

const std::vector<std::string> Silence::getDescription() const {
  return std::vector<std::string>{"Enchanted minion cannot use", "abilities",
                                  ""};
}

bool Silence::useCardAbility(Player& activePlayer, Player& inactivePlayer,
                             TriggerType type) {
  std::cout
      << "This minion is enchanted with Silence, and cannot play abilities."
      << std::endl;
  return false;
}

bool Silence::useCardAbility(Player& targetPlayer, Card& targetCard,
                             TriggerType type) {
  std::cout
      << "This minion is enchanted with Silence, and cannot play abilities."
      << std::endl;
  return false;
}
