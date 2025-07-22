#ifndef ABILITY_H_
#define ABILITY_H_

#include <string>
#include <vector>

class Player;

enum class TriggerType {
  None,
  StartOfTurn,
  EndOfTurn,
  MinionEnters,
  MinionLeaves
};

enum class TargetType { Minion, Ritual };

class Ability {
  std::string name;
  int cost;
  std::vector<TargetType> validTargets;

 public:
  Ability(const std::string& name, int cost,
          std::vector<TargetType> validTargets = {});

  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) = 0;

  bool requiresTarget() const;
  bool canTarget(TargetType targetType) const;
};

#endif
