#include "Minion.h"

#include <iostream>
#include <memory>
#include <string>

#include "Player.h"

Minion::Minion(const std::string& name, int cost, int attack, int defence,
               std::unique_ptr<const Ability> ability)
    : Card{name, cost, CardType::Minion, std::move(ability)},
      attack{attack},
      defence{defence},
      actions{0} {}

Minion::~Minion() {}

void Minion::attackMinion(Minion& targetMinion) {
  targetMinion.adjustDefence(-attack);
  adjustDefence(-targetMinion.attack);
}

void Minion::attackPlayer(Player& targetPlayer) {
  targetPlayer.adjustLife(-attack);
}

bool Minion::useCardAbility(Player& activePlayer, Player& inactivePlayer,
                            TriggerType type = TriggerType::None) {
  if (actions != 0) {
    std::cerr << "Minion does not have enough actions." << std::endl;
    return false;
  }
  if (Card::useCardAbility(activePlayer, inactivePlayer, type)) {
    actions--;
    return true;
  }
}

bool Minion::useCardAbility(Player& targetPlayer, Card& targetCard,
                            TriggerType type = TriggerType::None) {
  if (actions != 0) {
    std::cerr << "Minion does not have enough actions." << std::endl;
    return false;
  }
  if (Card::useCardAbility(targetPlayer, targetCard, type)) {
    actions--;
    return true;
  }
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

void Minion::adjustAttack(int amount) { attack += amount; }

void Minion::adjustDefence(int amount) { defence += amount; }

void Minion::resetActions() { actions = 1; }
