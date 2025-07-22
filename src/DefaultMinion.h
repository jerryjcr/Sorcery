#ifndef DEFAULTMINION_H_
#define DEFAULTMINION_H_

#include "Card.h"
#include "Minion.h"

// for testing
class DefaultMinion : public Minion {
 public:
  DefaultMinion();
  ~DefaultMinion() = default;
  const std::vector<const std::string>& getDescription() const override;
};

#endif
