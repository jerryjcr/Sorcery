#include "Minion.h"

Minion::Minion(const std::string& name, int cost, int attack, int defence,
               std::shared_ptr<const Ability> activated,
               std::shared_ptr<const Ability> triggered)
    : Card{name, cost, activated, triggered},
      attack{attack},
      defence{defence},
      actions{1} {}

void Minion::attackMinion(Minion& targetMinion) {
  // fill in later
}

void Minion::attackPlayer(Player& targetPlayer) {
  targetPlayer.adjustLife(-1 * attack);
  // maybe you want to check if this attack wins the game or not
}

int Minion::getAttack() const { return attack; }

int Minion::getDefence() const { return defence; }

int Minion::getActions() const { return actions; }

void Minion::adjustAttack(int amount) { attack += amount; }

void Minion::adjustDefence(int amount) { defence += amount; }

void Minion::resetActions() { actions = 1; }
