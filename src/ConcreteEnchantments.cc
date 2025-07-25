#include "ConcreteEnchantments.h"

#include <iostream>

GiantStrength::GiantStrength() : Enchantment{"Giant Strength", 1} {}

GiantStrength::GiantStrength(std::unique_ptr<Minion> parent)
    : Enchantment{"Giant Strength", 1, std::move(parent)} {}

const std::vector<std::string> GiantStrength::getEnchantDescription() const {
  return std::vector<std::string>{"", "", "", "------                   ------",
                                  " +2  |                   | +2"};
}

int GiantStrength::getAttack() const { return parent->getAttack() + 2; }

int GiantStrength::getDefence() const { return parent->getDefence() + 2; }

Enrage::Enrage() : Enchantment{"Enrage", 2}, attackRemainder{0}, damageRemainder{0} {}

Enrage::Enrage(std::unique_ptr<Minion> parent)
    : Enchantment{"Enrage", 2, std::move(parent)}, attackRemainder{0}, damageRemainder{0} {}

const std::vector<std::string> Enrage::getEnchantDescription() const {
  return std::vector<std::string>{"", "", "", "------                   ------",
                                  " *2  |                   | *2"};
}

int Enrage::getAttack() const { return (parent->getAttack() * 2)+attackRemainder; }

int Enrage::getDefence() const { return ((parent->getDefence() * 2)+damageRemainder); }

void Enrage::adjustDefence(int amount) {
  parent->adjustDefence(amount/2);
  damageRemainder+=amount%2;
  if (damageRemainder==2){
    parent->adjustDefence(1);
    damageRemainder=0;
  }
}

void Enrage::adjustAttack(int amount) {
  parent->adjustAttack(amount/2);
  attackRemainder+=amount%2;
  if (attackRemainder==2){
    parent->adjustAttack(1);
    attackRemainder=0;
  }
}

Haste::Haste() : Enchantment{"Haste", 1} {}

Haste::Haste(std::unique_ptr<Minion> parent)
    : Enchantment{"Haste", 1, std::move(parent)} {}

const std::vector<std::string> Haste::getEnchantDescription() const {
  return std::vector<std::string>{" Enchanted minion gains +1",
                                  " actions each turn.", "", "", ""};
}

int Haste::getActions() const { return parent->getActions() + 1; }

MagicFatigue::MagicFatigue() : Enchantment{"Magic Fatigue", 0} {}

MagicFatigue::MagicFatigue(std::unique_ptr<Minion> parent)
    : Enchantment{"Magic Fatigue", 0, std::move(parent)} {}

const std::vector<std::string> MagicFatigue::getEnchantDescription() const {
  return std::vector<std::string>{" Enchanted minion's activated",
                                  " ability costs 2 more", "", "", ""};
}

int MagicFatigue::getAbilityCost() const {
  return parent->getAbilityCost() + 2;
}

Silence::Silence() : Enchantment{"Silence", 1} {}

Silence::Silence(std::unique_ptr<Minion> parent)
    : Enchantment{"Silence", 1, std::move(parent)} {}

const std::vector<std::string> Silence::getEnchantDescription() const {
  return std::vector<std::string>{" Enchanted minion cannot use", "abilities",
                                  "", "", ""};
}

bool Silence::useCardAbility(Player& activePlayer, Player& inactivePlayer,
                             TriggerType type) {
  if (type==TriggerType::None) std::cout
      << "This minion is enchanted with Silence, and cannot play abilities."
      << std::endl;
  return false;
}

bool Silence::useCardAbility(Player& targetPlayer, Card& targetCard,
                          Player& activePlayer, Player& otherPlayer,
                          TriggerType type) {
  if (type==TriggerType::None) std::cout
      << "This minion is enchanted with Silence, and cannot play abilities."
      << std::endl;
  return false;
}
