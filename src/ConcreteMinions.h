#ifndef CONCRETEMINIONS_H_
#define CONCRETEMINIONS_H_

#include "Card.h"
#include "ConcreteAbilities.h"
#include "Minion.h"

class DefaultMinion : public Minion {
 public:
  DefaultMinion();
  ~DefaultMinion() = default;
  void describe() const;
};

class AirElemental : public Minion {
  public:
    AirElemental();
    void describe() const override;
};

#endif
