#ifndef CONCRETEMINIONS_H_
#define CONCRETEMINIONS_H_

#include "Card.h"
#include "Minion.h"

// for testing
class DefaultMinion : public Minion {
 public:
  DefaultMinion();
  ~DefaultMinion() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

class AirElemental : public Minion {
 public:
  AirElemental();
  ~AirElemental() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

class EarthElemental : public Minion {
 public:
  EarthElemental();
  ~EarthElemental() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

class BoneGolem : public Minion {
 public:
  BoneGolem();
  ~BoneGolem() = default;
  virtual bool useCardAbility(Player& targetPlayer, Card& targetCard,
                          Player& otherPlayer,
                          TriggerType type = TriggerType::None) override;
  // override in order to ensure target is itself
  virtual bool useCardAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type = TriggerType::None);
  virtual const std::vector<std::string> getDescription() const override;
};

class FireElemental : public Minion {
 public:
  FireElemental();
  ~FireElemental() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

class PotionSeller : public Minion {
 public:
  PotionSeller();
  ~PotionSeller() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

class NovicePyromancer : public Minion {
 public:
  NovicePyromancer();
  ~NovicePyromancer() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

class ApprenticeSummoner : public Minion {
 public:
  ApprenticeSummoner();
  ~ApprenticeSummoner() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

class MasterSummoner : public Minion {
 public:
  MasterSummoner();
  ~MasterSummoner() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

#endif
