#ifndef CONCRETEABILITIES_H_
#define CONCRETEABILITIES_H_

#include "Ability.h"

class BanishAbility : public Ability {
  public:
    BanishAbility(int cost);
    virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) override;
};

class UnsummonAbility : public Ability {
  public:
    UnsummonAbility(int cost);
    virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) override;
};

class RechargeAbility : public Ability {
  public:
    RechargeAbility(int cost);
    virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) override;
};

class DisenchantAbility : public Ability {
  public:
    DisenchantAbility(int cost);
    virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) override;
};

class RaiseDeadAbility : public Ability {
  public:
    RaiseDeadAbility(int cost);
    virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) override;
};

//only effects the targetted player, so it must be called twice for the intended effect
class BlizzardAbility : public Ability {
  public:
    BlizzardAbility(int cost);
    virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) override;
};

//adds 1/1 to target minion on minion leave
class BoneGolemAbility : public Ability {
  public:
    BoneGolemAbility(int cost);
    virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) override;
};

//deal 1 damage on minion enter
class FireElementalAbility : public Ability {
  public:
    FireElementalAbility(int cost);
    virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) override;
};

//+0/1 to all your minions on turn end
class PotionSellerAbility : public Ability {
  public:
    PotionSellerAbility(int cost);
    virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) override;
};

//1 damage to target minion
class NovicePyromancerAbility : public Ability {
  public:
    NovicePyromancerAbility(int cost);
    virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) override;
};

//summon a 1/1 air elemental, cannot be used if board is full
class ApprenticeSummonerAbility : public Ability {
  public:
    ApprenticeSummonerAbility(int cost);
    virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) override;
};

//summon up to 3 air elementals, cannot be used if board is full
class MasterSummonerAbility : public Ability {
  public:
    MasterSummonerAbility(int cost);
    virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) override;
};

//gain 1 magic on turn start
class DarkRitualAbility : public Ability {
  public:
    DarkRitualAbility(int cost);
    virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) override;
};

//give +1/1 on minion enter
class AuraOfPowerAbility : public Ability {
  public:
    AuraOfPowerAbility(int cost);
    virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) override;
};

//destoys minion on enter
class StandstillAbility : public Ability {
  public:
    StandstillAbility(int cost);
    virtual void useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) override;
};

#endif
