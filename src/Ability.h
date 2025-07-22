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
  int cost;
  std::vector<TargetType> validTargets;

 public:
  Ability(int cost,
          std::vector<TargetType> validTargets = {});
  //if the trigger type is minionenter,or minionleave, targetplayer is owner of target card, which is the trigger minion
  //if the trigger type is none, targetplayer is owner of the card that called it, not the owner of the target card
  //if the trigger type is start/end of turn, targetplayer is the player whos turn just started/ended
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card>& target) = 0;

  bool requiresTarget() const;
  bool canTarget(TargetType targetType) const;
  int getAbilityCost() const;
};

#endif
