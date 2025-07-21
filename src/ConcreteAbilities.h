#ifndef CONCRETEABILITIES_H_
#define CONCRETEABILITIES_H_

#include "Ability.h"

class Player;

class BanishAbility : public Ability {
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) override;
};

class UnsummonAbility : public Ability {
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) override;
};

class RechargeAbility : public Ability {
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) override;
};

class DisenchantAbility : public Ability {
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) override;
};

class RaiseDeadAbility : public Ability {
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) override;
};

//only effects the targetted player, so it must be called twice for the intended effect
class BlizzardAbility : public Ability {
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) override;
};

//adds 1/1 to target minion on minion leave
class BoneGolemAbility : public Ability {
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) override;
};

//deal 1 damage on minion enter
class FireElementalAbility : public Ability {
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) override;
};

//+0/1 to all your minions on turn end
class PotionSellerAbility : public Ability {
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) override;
};

//1 damage to target minion
class NovicePyromancerAbility : public Ability {
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) override;
};

//summon a 1/1 air elemental, cannot be used if board is full
class ApprenticeSummonerAbility : public Ability {
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) override;
};

//summon up to 3 air elementals, cannot be used if board is full
class MasterSummonerAbility : public Ability {
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) override;
};

//gain 1 magic on turn start
class DarkRitualAbility : public Ability {
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) override;
};

//give +1/1 on minion enter
class AuraOfPowerAbility : public Ability {
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) override;
};

//destoys minion on enter
class StandstillAbility : public Ability {
  virtual void useAbility(TriggerType type, Player& targetPlayer,
                          int boardIndex) override;
};

#endif
