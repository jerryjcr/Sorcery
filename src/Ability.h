#ifndef ABILITY_H_
#define ABILITY_H_

#include "Card.h"
#include "Player.h"

enum class TriggerType {
  None,
  StartOfTurn,
  EndOfTurn,
  MinionEnters,
  MinionLeaves
};

class Ability {
  int abilityCost;

 public:
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) = 0;
};

#endif
