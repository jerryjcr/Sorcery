#ifndef CONCRETEENCHANTMENTS_H_
#define CONCRETEENCHANTMENTS_H_

#include "Enchantment.h"

class GiantStrength : public Enchantment {
 public:
  GiantStrength();
  GiantStrength(std::unique_ptr<Minion> parent);
  ~GiantStrength() = default;
  virtual const std::vector<std::string> getEnchantDescription() const override;
  virtual int getAttack() const override;
  virtual int getDefence() const override;
};

class Enrage : public Enchantment {
 public:
  Enrage();
  Enrage(std::unique_ptr<Minion> parent);
  ~Enrage() = default;
  virtual const std::vector<std::string> getEnchantDescription() const override;
  virtual int getAttack() const override;
  virtual int getDefence() const override;
};

class Haste : public Enchantment {
 public:
  Haste();
  Haste(std::unique_ptr<Minion> parent);
  ~Haste() = default;
  virtual const std::vector<std::string> getEnchantDescription() const override;
  virtual int getActions() const override;
};

class MagicFatigue : public Enchantment {
 public:
  MagicFatigue();
  MagicFatigue(std::unique_ptr<Minion> parent);
  ~MagicFatigue() = default;
  virtual const std::vector<std::string> getEnchantDescription() const override;
  virtual int getAbilityCost() const override;
};

class Silence : public Enchantment {
 public:
  Silence();
  Silence(std::unique_ptr<Minion> parent);
  ~Silence() = default;
  virtual const std::vector<std::string> getEnchantDescription() const override;
  virtual bool useCardAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type = TriggerType::None) override;
  virtual bool useCardAbility(Player& targetPlayer, Card& targetCard,
                          Player& otherPlayer,
                          TriggerType type = TriggerType::None) override;
};

#endif
