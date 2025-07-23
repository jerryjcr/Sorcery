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
  CardType type;
  std::unique_ptr<const Ability> ability;

 public:
  Card(const std::string& name, int cost, CardType type,
       std::unique_ptr<const Ability> ability);
  virtual ~Card() = 0;

  // uses an ability without a target
  virtual bool useCardAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type = TriggerType::None);
  // uses an ability with a target
  virtual bool useCardAbility(Player& targetPlayer, Card& targetCard,
                              TriggerType type = TriggerType::None);

  const std::string& getName() const;
  int getCost() const;
  CardType getType() const;
  virtual const std::vector<std::string>& getDescription() const = 0;
};

#endif
