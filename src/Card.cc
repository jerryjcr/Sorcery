#include "Card.h"

Card::Card(const std::string& name, int cost,
           std::shared_ptr<const Ability> activated,
           std::shared_ptr<const Ability> triggered)
    : name{name},
      cost{cost},
      activatedAbility{activated},
      triggeredAbility{triggered} {}

void Card::activateAbility(Card* target, Player& activePlayer,
                           Player& inactivePlayer) {
  // figure this out later
}

void Card::triggerAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) {
  // figure this out later
}

int Card::getCost() const { return cost; }
