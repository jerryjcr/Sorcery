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
  std::unique_ptr<const Ability> ability;

 public:
  Card(const std::string& name, int cost,
       std::unique_ptr<const Ability> ability = nullptr);
  virtual ~Card() = 0;

  // uses an ability without a target
  virtual void useCardAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type = TriggerType::None);
  // uses an ability with a target
  virtual void useCardAbility(Player& targetPlayer,
                              std::unique_ptr<Card>& targetCard,
                              TriggerType type = TriggerType::None);

  const std::string& getName() const;
  int getCost() const;
};

#endif
