#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Card.h"
#include "Database.h"
#include "Minion.h"
#include "Player.h"
#include "Ritual.h"

int main(int argc, char* argv[]) {
  // processing command line args
  bool testingMode = false;
  bool graphicsMode = false;
  std::string decklist1 = "default.txt";
  std::string decklist2 = "default.txt";

  for (int i = 1; i < argc; i++) {
    std::string cmd = argv[i];

    if (cmd == "-deck1") {
      // should check for invalid input here (no file given)
      i++;
      decklist1 = argv[i];
    } else if (cmd == "-deck2") {
      // should check for invalid input here (no file given)
      i++;
      decklist2 = argv[i];
    } else if (cmd == "-init") {
      //... do this later
    } else if (cmd == "-testing") {
      testingMode = true;
    } else if (cmd == "-graphics") {
      graphicsMode = true;
    }
  }

  // here we would create the decks

  // the idea is that we read some sort of id from the file
  // then match that so some sort of database and get the right values for that
  // specifc card
  std::ifstream deckfile1{decklist1};
  std::ifstream deckfile2{decklist2};
  std::vector<std::unique_ptr<Card>> deck1;
  std::vector<std::unique_ptr<Card>> deck2;
  std::string currCard;

  while (deckfile1 >> currCard) {
    std::unique_ptr<Card> newCard(findCard(currCard));
    deck1.emplace_back(std::move(newCard));
  }

  while (deckfile2 >> currCard) {
    std::unique_ptr<Card> newCard(findCard(currCard));
    deck2.emplace_back(std::move(newCard));
  }

  // when we add -init, this will have to change, amoung other things
  std::string name1, name2;
  std::cin >> name1;
  std::cin >> name2;

  Player p1{name1, std::move(deck1)};
  Player p2{name2, std::move(deck2)};

  // main loop
  while (true) {
    // due later do later
  }
}
