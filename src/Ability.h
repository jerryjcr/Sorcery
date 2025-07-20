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
 public:
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) = 0;
};

#endif
