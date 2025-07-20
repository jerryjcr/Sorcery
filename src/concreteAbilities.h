#ifndef CONCRETEABILITIES_H_
#define CONCRETEABILITIES_H_

#include "Ability.h"

class BanishAbility : public Ability{
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) override;
};

class UnsummonAbility : public Ability{
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) override;
};

class RechargeAbility : public Ability{
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) override;
};

class DisenchantAbility : public Ability{
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) override;
};

class RaiseDeadAbility : public Ability{
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) override;
};

class BlizzardAbility : public Ability{
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) override;
};

class BoneGolemAbility : public Ability{
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) override;
};

class FireElementalAbility : public Ability{
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) override;
};

class PotionSellerAbility : public Ability{
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) override;
};

class NovicePyromancerAbility : public Ability{
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) override;
};

class ApprenticeSummonerAbility : public Ability{
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) override;
};

class MasterSummonerAbility : public Ability{
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) override;
};

class DarkRitualAbility : public Ability{
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) override;
};

class AuraOfPowerAbility : public Ability{
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) override;
};

class StandstillAbility : public Ability{
  virtual void useAbility(TriggerType type, Card* target, Player& activePlayer,
                          Player& inactivePlayer) override;
};


#endif