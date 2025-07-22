#ifndef CARD_H_
#define CARD_H_

#include <memory>
#include <string>

#include "Ability.h"

class Player;

class Card {
 protected:
  std::string name;
  int cost;
  std::shared_ptr<const Ability> activatedAbility = nullptr;
  std::shared_ptr<const Ability> triggeredAbility = nullptr;

 public:
  Card(const std::string& name, int cost,
       std::shared_ptr<const Ability> activated = nullptr,
       std::shared_ptr<const Ability> triggered = nullptr);
  virtual ~Card() = default;

  // uses an activated ability without a target
  virtual void activateAbility();
  // uses an activated ability with a target
  virtual void activateAbility(Player& targetPlayer, int targetIndex);
  // uses a trigger ability (ability compares trigger type)
  virtual void triggerAbility(TriggerType type, Player& targetPlayer,
                              int targetIndex);
  virtual void describe() const = 0;

  int getCost() const;
};

#endif
