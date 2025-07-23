#ifndef CONCRETEMINION_H_
#define CONCRETEMINION_H_

#include "Minion.h"

class DefaultMinion : public Minion {
 public:
  DefaultMinion();
  ~DefaultMinion() = default;
  const std::vector<std::string>& getDescription() const override;
};

class AirElemental : public Minion {
 public:
  AirElemental();
  ~AirElemental() = default;
  const std::vector<std::string>& getDescription() const override;
};

class EarthElemental : public Minion {
 public:
  EarthElemental();
  ~EarthElemental() = default;
  const std::vector<std::string>& getDescription() const override;
};
/*
class FireElemental : public Minion {
 public:
  FireElemental();
  ~FireElemental() = default;
  const std::vector<std::string>& getDescription() const override;
};
*/

#endif
