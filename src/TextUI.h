#ifndef TEXTUI_H_
#define TEXTUI_H_

#include <iostream>
#include <string>
#include <vector>
#include <istream>
#include <fstream>

#include "Card.h"
#include "Enchantment.h"
#include "Minion.h"
#include "Ritual.h"
#include "Spell.h"

void printHand(Player& p1);
void printBoard(Player& active, Player& opponent);
void printSorcery();

#endif
