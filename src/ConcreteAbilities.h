#ifndef CONCRETEABILITIES_H_
#define CONCRETEABILITIES_H_

#include "Ability.h"

class BanishAbility : public Ability {
  public:
    BanishAbility(int cost);
    virtual bool useAbility(Player& targetPlayer,
                              Card& targetCard,
                              TriggerType type = TriggerType::None) override;
};

class UnsummonAbility : public Ability {
  public:
    UnsummonAbility(int cost);
    virtual bool useAbility(Player& targetPlayer,
                              Card& targetCard,
                              TriggerType type = TriggerType::None) override;
};

class RechargeAbility : public Ability {
  public:
    RechargeAbility(int cost);
    virtual bool useAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type = TriggerType::None) override;
};

class DisenchantAbility : public Ability {
  public:
    DisenchantAbility(int cost);
    virtual bool useAbility(Player& targetPlayer,
                              Card& targetCard,
                              TriggerType type = TriggerType::None) override;
};

class RaiseDeadAbility : public Ability {
  public:
    RaiseDeadAbility(int cost);
    virtual bool useAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type = TriggerType::None) override;
};

class BlizzardAbility : public Ability {
  public:
    BlizzardAbility(int cost);
    virtual bool useAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type = TriggerType::None) override;
};

//adds 1/1 to target minion on minion leave
//special case, target here is always itself instead of the leaving minion
class BoneGolemAbility : public Ability {
  public:
    BoneGolemAbility(int cost);
    virtual bool useAbility(Player& targetPlayer,
                              Card& targetCard,
                              TriggerType type = TriggerType::None) override;
};

//deal 1 damage on minion enter
class FireElementalAbility : public Ability {
  public:
    FireElementalAbility(int cost);
    virtual bool useAbility(Player& targetPlayer,
                              Card& targetCard,
                              TriggerType type = TriggerType::None) override;
};

//+0/1 to all your minions on turn end
class PotionSellerAbility : public Ability {
  public:
    PotionSellerAbility(int cost);
    virtual bool useAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type = TriggerType::None) override;
};

//1 damage to target minion
class NovicePyromancerAbility : public Ability {
  public:
    NovicePyromancerAbility(int cost);
    virtual bool useAbility(Player& targetPlayer,
                              Card& targetCard,
                              TriggerType type = TriggerType::None) override;
};

//summon a 1/1 air elemental, cannot be used if board is full
class ApprenticeSummonerAbility : public Ability {
  public:
    ApprenticeSummonerAbility(int cost);
    virtual bool useAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type = TriggerType::None) override;
};

//summon up to 3 air elementals, cannot be used if board is full
class MasterSummonerAbility : public Ability {
  public:
    MasterSummonerAbility(int cost);
    virtual bool useAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type = TriggerType::None) override;
};

//gain 1 magic on turn start
class DarkRitualAbility : public Ability {
  public:
    DarkRitualAbility(int cost);
    virtual bool useAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type = TriggerType::None) override;
};

//give +1/1 on minion enter
class AuraOfPowerAbility : public Ability {
  public:
    AuraOfPowerAbility(int cost);
    virtual bool useAbility(Player& targetPlayer,
                              Card& targetCard,
                              TriggerType type = TriggerType::None) override;
};

//destoys minion on enter
class StandstillAbility : public Ability {
  public:
    StandstillAbility(int cost);
    virtual bool useAbility(Player& targetPlayer,
                              Card& targetCard,
                              TriggerType type = TriggerType::None) override;
};

#endif
