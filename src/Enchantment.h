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

  virtual CardType getType() const override;
  // if parent is nullptr, then the object is a pure enchantment, so we output
  // the enchantment name and cost if parent is not, then the object is an
  // enchanted minion, so we output the minion name and cost
  virtual int getCost() const override;
  virtual const std::string& getName() const override;
};

#endif
