#ifndef ENCHANTMENT_H_
#define ENCHANTMENT_H_

#include "Minion.h"

class Enchantment : public Minion {
  std::unique_ptr<Minion> parent;
  public:
    Enchantment(std::unique_ptr<Minion> parent);
    std::unique_ptr<Minion>& getParent() const;
    virtual ~Enchantment()=0;
};



#endif