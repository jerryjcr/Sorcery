#ifndef ABILITY_H_
#define ABILITY_H_

#include <string>
#include <vector>

class Player;
class Card;

enum class TriggerType {
  None,
  MyStartOfTurn,
  OpponentStartOfTurn,
  MyEndOfTurn,
  OpponentEndOfTurn,
  MyMinionEnters,
  OpponentMinionEnters,
  MyMinionLeaves,
  OpponentMinionLeaves
};

enum class CardType { Minion, Enchantment, Spell, Ritual };

class Ability {
  int cost;
  std::vector<CardType> validTargets;

 public:
  Ability(int cost, std::vector<CardType> validTargets = {});
  // no target
  virtual bool useAbility(Player& activePlayer, Player& inactivePlayer,
                          TriggerType type = TriggerType::None);
  // target
  virtual bool useAbility(Player& targetPlayer, Card& targetCard,
                          Player& otherPlayer,
                          TriggerType type = TriggerType::None);

  bool requiresTarget() const;
  bool canTarget(CardType targetType) const;
  int getAbilityCost() const;
};

#endif
