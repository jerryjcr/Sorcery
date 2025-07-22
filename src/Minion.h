#ifndef MINION_H_
#define MINION_H_

#include <memory>
#include <string>

#include "Ability.h"
#include "Card.h"

class Player;

class Minion : public Card {
 protected:
  int attack;
  int defence;
  int actions;

 public:
  Minion(const std::string& name, int cost, int attack, int defence,
         std::unique_ptr<const Ability> ability = nullptr);
  virtual ~Minion() = 0;

  void attackMinion(Minion& targetMinion);
  void attackPlayer(Player& targetPlayer);

  virtual bool useCardAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type = TriggerType::None) override;
  virtual bool useCardAbility(Player& targetPlayer,
                              std::unique_ptr<Card>& targetCard,
                              TriggerType type = TriggerType::None) override;

  bool requiresTarget() const;
  bool canTarget(CardType targetType) const;

  // enchantments can override these methods or Card's ability methods
  virtual int getAttack() const;
  virtual int getDefence() const;
  virtual int getActions() const;
  virtual const std::vector<std::string>& getDescription() const override = 0;

  void adjustAttack(int amount);
  void adjustDefence(int amount);

  // sets actions to 1
  void resetActions();
};

#endif
