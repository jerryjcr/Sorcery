#ifndef RITUAL_H_
#define RITUAL_H_

#include <memory>
#include <string>

#include "Ability.h"
#include "Card.h"
#include "Player.h"

class Ritual : public Card {
 protected:
  int charges, chargeCost;

 public:
  Ritual(const std::string& name, int cost, int charges, int chargeCost,
         std::unique_ptr<const Ability> ability);
  virtual ~Ritual() = 0;

  void useRitual(TriggerType type, Player& targetPlayer, int boardIndex);

  void adjustCharges(int amount);
  int getCharges() const;
};

#endif
