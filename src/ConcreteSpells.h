#ifndef CONCRETESPELLS_H_
#define CONCRETESPELLS_H_

#include "Spell.h"

class Banish : public Spell {
 public:
  Banish();
  virtual ~Banish() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

class Unsummon : public Spell {
 public:
  Unsummon();
  virtual ~Unsummon() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

class Recharge : public Spell {
 public:
  Recharge();
  virtual ~Recharge() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

class Disenchant : public Spell {
 public:
  Disenchant();
  virtual ~Disenchant() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

class RaiseDead : public Spell {
 public:
  RaiseDead();
  virtual ~RaiseDead() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

class Blizzard : public Spell {
 public:
  Blizzard();
  virtual ~Blizzard() = default;
  virtual const std::vector<std::string> getDescription() const override;
};

#endif
