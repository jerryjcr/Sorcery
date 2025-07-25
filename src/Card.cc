#include "Card.h"

#include <memory>
#include <string>
#include <iostream>

#include "Ability.h"
#include "Player.h"

Card::Card(const std::string& name, int cost, CardType type,
           std::unique_ptr<Ability> ability)
    : name{name}, cost{cost}, type{type}, ability{std::move(ability)} {}

Card::~Card() {}

bool Card::useCardAbility(Player& activePlayer, Player& inactivePlayer,
                          TriggerType type) {
  if (!ability) {
    if (type==TriggerType::None) std::cerr<<"Minion has no ability"<<std::endl;
    return false;
  }
  return ability->useAbility(activePlayer, inactivePlayer, type);
}

bool Card::useCardAbility(Player& targetPlayer, Card& targetCard,
                          Player& activePlayer, Player& otherPlayer,
                          TriggerType type) {
  if (!ability) {
     if (type==TriggerType::None) std::cerr<<"Minion has no ability"<<std::endl;
    return false;
  }
  return ability->useAbility(targetPlayer, targetCard, activePlayer, otherPlayer, type);
}

const std::string& Card::getName() const { return name; }

int Card::getCost() const { return cost; }

CardType Card::getType() const { return type; }
