#ifndef CONCRETEMINIONS_H_
#define CONCRETEMINIONS_H_

#include "Card.h"
#include "ConcreteAbilities.h"
#include "Minion.h"

class AirElemental : public Minion {
  public:
    AirElemental();
    ~AirElemental() = default;
    virtual void describe() const override;
};

class EarthElemental : public Minion {
  public:
    EarthElemental();
    ~EarthElemental() = default;
    virtual void describe() const override;
};

class BoneGolem : public Minion {
  public:
    BoneGolem();
    ~BoneGolem() = default;
    virtual void triggerAbility(TriggerType type, Player& targetPlayer,
                              int boardIndex) override;//override in order to ensure target is itself
    virtual void describe() const override;
};

class FireElemental : public Minion {
  public:
    FireElemental();
    ~FireElemental() = default;
    virtual void describe() const override;
};

class PotionSeller : public Minion {
  public:
    PotionSeller();
    ~PotionSeller() = default;
    virtual void describe() const override;
};

class NovicePyromancer : public Minion {
  public:
    NovicePyromancer();
    ~NovicePyromancer() = default;
    virtual void describe() const override;
};

class ApprenticeSummoner : public Minion {
  public:
    ApprenticeSummoner();
    ~ApprenticeSummoner() = default;
    virtual void activateAbility(Player& targetPlayer, int boardIndex) override;//override for error checking
    virtual void describe() const override;
};

class MasterSummoner : public Minion {
  public:
    MasterSummoner();
    ~MasterSummoner() = default;
    virtual void activateAbility(Player& targetPlayer, int boardIndex) override;//override for error checking
    virtual void describe() const override;
};

#endif
