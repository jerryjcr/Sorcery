#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Card.h"
#include "Database.h"
#include "Minion.h"
#include "Player.h"
#include "Ritual.h"

const int kStartOfTurnMagic = 1;

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

  Player& activePlayer = p1;
  Player& opponentPlayer = p2;
  while (true) {
    // start of turn

    // gain 1 magic
    activePlayer.adjustMagic(kStartOfTurnMagic);
    // draw a card
    activePlayer.drawCard();

    // start of turn effects trigger
    // do this later

    // "action phase"
    while (true) {
      // have to change the way that input works with the -init command
      std::string cmd;
      std::getline(std::cin, cmd);
      std::stringstream currline{cmd};
      cmd.clear();
      currline >> cmd;

      if (cmd == "help") {
        // help message goes here do if you are bored

      } else if (cmd == "end") {
        break;

      } else if (cmd == "quit") {
        return 0;

      } else if (cmd == "draw" && testingMode) {
        activePlayer.drawCard();

      } else if (cmd == "discard" && testingMode) {
        int handInd;
        if (currline >> handInd) {
          activePlayer.discard(handInd);
        } else {
          std::cerr << "Error, no hand index given" << std::endl;
        }

      } else if (cmd == "attack") {
        int myMinion;
        int target;
        if (currline >> myMinion) {
          // player checks if myMinion is out of range
          if (currline >> target && currline.peek() == EOF) {
            activePlayer.attackMinion(myMinion, opponentPlayer, target);
          } else if (currline.eof()) {
            // attacking the other player
            activePlayer.attackPlayer(myMinion, opponentPlayer);
          } else {
            std::cerr << "Invalid input, expected an integer to target"
                      << std::endl;
          }
        } else {
          std::cerr << "Error, no minon index given" << std::endl;
        }

      } else if (cmd == "play") {
        int myCard;
        int targetPlayer;
        char targetCard;
        if (currline >> myCard) {
          if (currline >> targetPlayer) {
            if (currline >> targetCard && currline.peek() == EOF) {
              if ((targetPlayer != 1 && targetPlayer != 2) ||
                  (targetCard != 'r' &&
                   (targetCard < '1' || targetCard > '5'))) {
                std::cerr << "Invalid input, player and or card targets are "
                             "out of range"
                          << std::endl;
              } else {
                int targetInd;
                // we all agree that 0 is how you target a ritual
                targetCard == 'r' ? targetInd = 0
                                  : targetInd = targetCard - '0';

                // this is weird since the players may forget who player 1 and 2
                // are, perhaps send a message reminding them?
                if (targetPlayer == 1) {
                  activePlayer.playCard(myCard, p1, targetCard);
                } else {  // must be targeting player 2
                  activePlayer.playCard(myCard, p2, targetCard);
                }
              }
            } else {
              std::cerr << "Invalid input, expected an integer" << std::endl;
            }
          } else if (currline.eof()) {
            activePlayer.playCard(myCard);
          } else {
            std::cerr << "Invalid input, expected an integer" << std::endl;
          }
        } else {
          std::cerr << "error, no card index give" << std::endl;
        }

      } else if (cmd == "use") {
        // do later since abilities aren't done yet
      } else if (cmd == "describe") {
        // todo
      } else if (cmd == "hand") {
        // do later
      } else if (cmd == "board") {
        // do later
      }
    }

    // end of turn
    // activate end of turn triggers (do later)
    //...
    std::swap(activePlayer, opponentPlayer);
  }
}
