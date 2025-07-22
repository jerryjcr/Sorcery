#include "Minion.h"

#include <memory>
#include <string>

#include "Player.h"

bool Minion::useAction() {
  if (actions == 0) {
    return false;
  } else {
    actions--;
    return true;
  }
}

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

bool Minion::requiresTarget() const {
  return ability ? ability->requiresTarget() : false;
};

bool Minion::canTarget(CardType targetType) const {
  return ability ? ability->canTarget(type) : false;
}

int Minion::getAttack() const { return attack; }

int Minion::getDefence() const { return defence; }

int Minion::getActions() const { return actions; }

void Minion::adjustAttack(int amount) { attack += amount; }

void Minion::adjustDefence(int amount) { defence += amount; }

void Minion::resetActions() { actions = 1; }
