#include "Ability.h"
#include "Card.h"

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

Ability::Ability(int cost,
                 std::vector<CardType> validTargets)
    : cost{cost}, validTargets{std::move(validTargets)} {}

bool Ability::requiresTarget() const { return !validTargets.empty(); }

bool Ability::canTarget(CardType targetType) const {
  return std::find(validTargets.begin(), validTargets.end(), targetType) !=
         validTargets.end();
}

int Ability::getAbilityCost() const {
  return cost;
}

void Ability::useAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type = TriggerType::None){
  if (this->requiresTarget()){
    std::cerr<<"cannot use targetted ability with no target"<<std::endl;
    return;
  }
}

void Ability::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard,
                              TriggerType type = TriggerType::None){
  if (!this->canTarget(targetCard->getType())){
    std::cerr<<"cannot target a card of this type"<<std::endl;
  }
}
