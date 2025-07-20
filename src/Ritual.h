#ifndef RITUAL_H_
#define RITUAL_H_

#include "Card.h"

class Ritual : public Card {
 protected:
  int charges, chargeCost;

 public:
  Ritual(const std::string& name, int cost, int charges, int chargeCost,
         std::shared_ptr<const Ability> triggered);
  virtual ~Ritual() = 0;

  void useRitual(TriggerType type, Player& targetPlayer,int boardIndex);

  void adjustCharges(int amount);
};

#endif
