#ifndef CARD_H
#define CARD_H

#include <string>

#include "Ability.h"  // for triggertype

class Player;

class Card {
 protected:
  std::string name;
  int cost;

 public:
  // uses an activated ability
  // target = nullptr if no target
  virtual void activateAbility(Card* target, Player& activePlayer,
                               Player& inactivePlayer);
  // uses a trigger ability (ability compares trigger type)
  virtual void triggerAbility(TriggerType type, Card* target,
                              Player& activePlayer, Player& inactivePlayer);
  virtual void describe() const = 0;

  virtual ~Card() = default;
};

#endif
