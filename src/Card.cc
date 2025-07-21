#include "Card.h"

Card::Card(const std::string& name, int cost,
           std::shared_ptr<const Ability> activated,
           std::shared_ptr<const Ability> triggered)
    : name{name},
      cost{cost},
      activatedAbility{activated},
      triggeredAbility{triggered} {}

void Card::activateAbility(Player& targetPlayer, int boardIndex) {
  // figure this out later
}

void Card::triggerAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) {
  // figure this out later
}

int Card::getCost() const { return cost; }
