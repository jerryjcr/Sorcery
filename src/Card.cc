#include "Card.h"

#include <memory>
#include <string>

#include "Ability.h"
#include "Player.h"

Card::Card(const std::string& name, int cost,
           std::shared_ptr<const Ability> activated,
           std::shared_ptr<const Ability> triggered)
    : name{name},
      cost{cost},
      activatedAbility{activated},
      triggeredAbility{triggered} {}

void Card::activateAbility() {
  // figure this out later
}

void Card::activateAbility(Player& targetPlayer, int targetIndex) {
  // figure this out later
}

void Card::triggerAbility(TriggerType type, Player& targetPlayer,
                          int targetIndex) {
  // figure this out later
}

int Card::getCost() const { return cost; }
