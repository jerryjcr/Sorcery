#ifndef TEXTUI_H_
#define TEXTUI_H_

#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>

#include "Card.h"
#include "Enchantment.h"
#include "Minion.h"
#include "Ritual.h"
#include "Spell.h"

void printHand(Player& p1);
void printBoard(Player& active, Player& opponent);
void printSorcery();
void inspectCard(Minion& m);

#endif
