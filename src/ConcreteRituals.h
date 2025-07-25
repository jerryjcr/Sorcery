#ifndef CONCRETERITUALS_H_
#define CONCRETERITUALS_H_
#include "Ritual.h"

class DarkRitual : public Ritual {
 public:
  DarkRitual();
  ~DarkRitual() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

class AuraOfPower : public Ritual {
 public:
  AuraOfPower();
  ~AuraOfPower() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

class Standstill : public Ritual {
 public:
  Standstill();
  ~Standstill() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

#endif
