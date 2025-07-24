#ifndef ENCHANTMENT_H_
#define ENCHANTMENT_H_

#include "Minion.h"

class Enchantment : public Minion {
 protected:
  std::unique_ptr<Minion> parent;

 public:
  Enchantment(const std::string& name, int cost);
  Enchantment(const std::string& name, int cost,
              std::unique_ptr<Minion> parent);
  std::unique_ptr<Minion>& getParent();
  void setParent(std::unique_ptr<Minion> parent);
  virtual ~Enchantment() = 0;

  virtual bool useCardAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type = TriggerType::None) override;
  virtual bool useCardAbility(Player& targetPlayer, Card& targetCard,
                              Player& otherPlayer,
                              TriggerType type = TriggerType::None) override;
  virtual CardType getType() const override;
  virtual bool requiresTarget() const override;
  virtual bool canTarget(CardType targetType) const override;
  virtual int getAttack() const override;
  virtual int getDefence() const override;
  virtual int getActions() const override;
  virtual int getAbilityCost() const override;
  virtual void adjustActions(int amount) override;
  virtual void adjustAttack(int amount) override;
  virtual void adjustDefence(int amount) override;
  virtual void resetActions() override;

  // if parent is nullptr, then the object is a pure enchantment, so we output
  // the enchantment name and cost if parent is not, then the object is an
  // enchanted minion, so we output the minion name and cost
  virtual int getCost() const override;
  virtual const std::string& getName() const override;
  const std::string& getEnchantName() const;

  virtual const std::vector<std::string> getDescription() const;
  virtual const std::vector<std::string> getEnchantDescription() const = 0;
};

#endif
