#ifndef CONCRETEABILITIES_H_
#define CONCRETEABILITIES_H_

#include "Ability.h"

class BanishAbility : public Ability{
  virtual void useAbility(TriggerType type, Player& targetPlayer,int boardIndex) override;
};

class UnsummonAbility : public Ability{
  virtual void useAbility(TriggerType type, Player& targetPlayer,int boardIndex) override;
};

class RechargeAbility : public Ability{
  virtual void useAbility(TriggerType type, Player& targetPlayer,int boardIndex) override;
};

class DisenchantAbility : public Ability{
  virtual void useAbility(TriggerType type, Player& targetPlayer,int boardIndex) override;
};

class RaiseDeadAbility : public Ability{
  virtual void useAbility(TriggerType type, Player& targetPlayer,int boardIndex) override;
};

class BlizzardAbility : public Ability{
  virtual void useAbility(TriggerType type, Player& targetPlayer,int boardIndex) override;
};

class BoneGolemAbility : public Ability{
  virtual void useAbility(TriggerType type, Player& targetPlayer,int boardIndex) override;
};

class FireElementalAbility : public Ability{
  virtual void useAbility(TriggerType type, Player& targetPlayer,int boardIndex) override;
};

class PotionSellerAbility : public Ability{
  virtual void useAbility(TriggerType type, Player& targetPlayer,int boardIndex) override;
};

class NovicePyromancerAbility : public Ability{
  virtual void useAbility(TriggerType type, Player& targetPlayer,int boardIndex) override;
};

class ApprenticeSummonerAbility : public Ability{
  virtual void useAbility(TriggerType type, Player& targetPlayer,int boardIndex) override;
};

class MasterSummonerAbility : public Ability{
  virtual void useAbility(TriggerType type, Player& targetPlayer,int boardIndex) override;
};

class DarkRitualAbility : public Ability{
  virtual void useAbility(TriggerType type, Player& targetPlayer,int boardIndex) override;
};

class AuraOfPowerAbility : public Ability{
  virtual void useAbility(TriggerType type, Player& targetPlayer,int boardIndex) override;
};

class StandstillAbility : public Ability{
  virtual void useAbility(TriggerType type, Player& targetPlayer,int boardIndex) override;
};


#endif