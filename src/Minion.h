#ifndef MINION_H_
#define MINION_H_

#include <memory>
#include <string>

#include "Card.h"

class Ability;
class Player;

class Minion : public Card {
 protected:
  int attack;
  int defence;
  int actions;
  bool isEnchanted;

  bool useAction();

 public:
  Minion(const std::string& name, int cost, int attack, int defence,
         std::shared_ptr<const Ability> activated = nullptr,
         std::shared_ptr<const Ability> triggered = nullptr, bool isEnchanted = false);
  virtual ~Minion() = 0;

  void attackMinion(Minion& targetMinion);
  void attackPlayer(Player& targetPlayer);

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
