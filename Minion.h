#ifndef MINION_H
#define MINION_H

#include "Card.h"

class Minion : public Card {
 protected:
  int attack;
  int defence;
  int actions;

  bool useAction();

 public:
  Minion(const std::string& name, int cost, int attack, int defence,
         std::shared_ptr<const Ability> activated = nullptr,
         std::shared_ptr<const Ability> triggered = nullptr);
  virtual ~Minion() = 0;

  void attackMinion(Minion& targetMinion);
  void attackPlayer(Player& targetPlayer);
  void describe() const override;

  // enchantments can override these methods or Card's ability methods
  virtual int getAttack() const;
  virtual int getDefence() const;
  virtual int getActions() const;

  void adjustAttack(int amount);
  void adjustDefence(int amount);
  // sets actions to 1
  void resetActions();
};

#endif
