#include "Ability.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Card.h"

Ability::Ability(int cost, std::vector<CardType> validTargets)
    : cost{cost}, validTargets{std::move(validTargets)} {}

bool Ability::requiresTarget() const { return !validTargets.empty(); }

bool Ability::canTarget(CardType targetType) const {
  return std::find(validTargets.begin(), validTargets.end(), targetType) !=
         validTargets.end();
}

int Ability::getAbilityCost() const { return cost; }

bool Ability::useAbility(Player& activePlayer, Player& inactivePlayer,
                         TriggerType type) {
  if (this->requiresTarget()&&type==TriggerType::None) {
    std::cerr << "Error: Cannot use this ability with no target." << std::endl;
  } else if (!this->requiresTarget()) {
    std::cerr << "Error: Function was not overridden correctly." << std::endl;
  }
  return false;
}

bool Ability::useAbility(Player& targetPlayer, Card& targetCard,
                          Player& activePlayer, Player& otherPlayer,
                          TriggerType type) {
  if (!this->canTarget(targetCard.getType())&&type==TriggerType::None) {
    std::cerr << "Error: Cannot target this card, or this ability may not "
                 "target a card."
              << std::endl;
  } else if (this->canTarget(targetCard.getType())) {
    std::cerr << "Error: Function was not overridden correctly." << std::endl;
  }
  return false;
}
