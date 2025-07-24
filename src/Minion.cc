#include "Minion.h"

#include <iostream>
#include <memory>
#include <string>

#include "Player.h"

Minion::Minion(const std::string& name, int cost, int attack, int defence,
               std::unique_ptr<Ability> ability)
    : Card{name, cost, CardType::Minion, std::move(ability)},
      attack{attack},
      defence{defence},
      actions{0} {}

Minion::~Minion() {}

void Minion::attackMinion(Minion& targetMinion) {
  if (getActions() <= 0) {
    std::cout << "Minion does not have enough actions." << std::endl;
    return;
  }
  targetMinion.adjustDefence(-getAttack());
  adjustDefence(-targetMinion.getAttack());
  adjustActions(-1);
}

void Minion::attackPlayer(Player& targetPlayer) {
  if (getActions() <= 0) {
    std::cout << "Minion does not have enough actions." << std::endl;
    return;
  }
  targetPlayer.adjustLife(-getAttack());
  adjustActions(-1);
}

bool Minion::useCardAbility(Player& activePlayer, Player& inactivePlayer,
                            TriggerType type) {
  if (getActions() <= 0 && type == TriggerType::None) {
    std::cout << "Minion does not have enough actions." << std::endl;
    return false;
  }
  if (Card::useCardAbility(activePlayer, inactivePlayer, type)) {
    if (type == TriggerType::None) adjustActions(-1);
    return true;
  }
  return false;
}

bool Minion::useCardAbility(Player& targetPlayer, Card& targetCard,
                            TriggerType type) {
  if (getActions() <= 0 && type == TriggerType::None) {
    std::cout << "Minion does not have enough actions." << std::endl;
    return false;
  }
  if (Card::useCardAbility(targetPlayer, targetCard, type)) {
    if (type == TriggerType::None) adjustActions(-1);
    return true;
  }
  return false;
}

bool Minion::requiresTarget() const {
  return ability ? ability->requiresTarget() : false;
};

bool Minion::canTarget(CardType targetType) const {
  return ability ? ability->canTarget(type) : false;
}

int Minion::getAttack() const { return attack; }

int Minion::getDefence() const { return defence; }

int Minion::getActions() const { return actions; }

int Minion::getAbilityCost() const { return ability->getAbilityCost(); }

void Minion::adjustActions(int amount) { actions += amount; }

void Minion::adjustAttack(int amount) { attack += amount; }

void Minion::adjustDefence(int amount) { defence += amount; }

void Minion::resetActions() { actions = 1; }
