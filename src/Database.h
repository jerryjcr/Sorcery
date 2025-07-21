#ifndef DATABASE_H_
#define DATABASE_H_

#include "Card.h"
#include "Minion.h"
#include "Ritual.h"
#include "Spell.h"

// assigns values to the given parameters based on the code given
// if the code is invalid will assign a default minion
std::unique_ptr<Card> findCard(const std::string& code);

#endif
