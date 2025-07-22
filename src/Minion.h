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

  bool useAction();

 public:
  Minion(const std::string& name, int cost, int attack, int defence,
         std::unique_ptr<const Ability> ability);
  virtual ~Minion() = 0;

  void attackMinion(Minion& targetMinion);
  void attackPlayer(Player& targetPlayer);

  bool requiresTarget() const;
  bool canTarget(TargetType targetType) const;

  // enchantments can override these methods or Card's ability methods
  virtual int getAttack() const;
  virtual int getDefence() const;
  virtual int getActions() const;

  void adjustAttack(int amount);
  void adjustDefence(int amount);
  // sets actions to 1
  void resetActions();
  bool getIsEnchanted() const;
};

#endif
