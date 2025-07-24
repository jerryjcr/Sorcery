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
         std::unique_ptr<Ability> ability);
  virtual ~Ritual() = 0;

  virtual bool useCardAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type = TriggerType::None) override;
  virtual bool useCardAbility(Player& targetPlayer, Card& targetCard,
                          Player& otherPlayer,
                          TriggerType type = TriggerType::None) override;

  void adjustCharges(int amount);
  int getCharges() const;
  virtual const std::vector<std::string> getDescription() const override = 0;
};

#endif
