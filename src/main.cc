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
#include "TextUI.h"

const int kStartOfTurnMagic = 1;

int main(int argc, char* argv[]) {
  // processing command line args
  bool testingMode = false;
  bool graphicsMode = false;
  // default.txt still needs to be made
  std::string decklist1 = "default.txt";
  std::string decklist2 = "default.txt";

  for (int i = 1; i < argc; i++) {
    std::string cmd = argv[i];

    if (cmd == "-deck1") {
      if (i + 1 >= argc) {
        std::cerr
            << "Error, no filename given for deck 1. Using default instead"
            << std::endl;
        decklist1 = "default.txt";
      } else {
        i++;
        decklist1 = argv[i];
      }
    } else if (cmd == "-deck2") {
      if (i + 1 >= argc) {
        std::cerr
            << "Error, no filename given for deck 2. Using default instead"
            << std::endl;
        decklist2 = "default.txt";
      } else {
        i++;
        decklist2 = argv[i];
      }
    } else if (cmd == "-init") {
      //... do this later
    } else if (cmd == "-testing") {
      testingMode = true;
    } else if (cmd == "-graphics") {
      graphicsMode = true;
    }
  }

  std::ifstream deckfile1{decklist1};
  std::ifstream deckfile2{decklist2};
  std::vector<std::unique_ptr<Card>> deck1;
  std::vector<std::unique_ptr<Card>> deck2;
  std::string currCard;

  // reading from the deck file,
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
  std::getline(std::cin, name1);
  std::getline(std::cin, name2);

  Player p1{name1, std::move(deck1)};
  Player p2{name2, std::move(deck2)};

  Player* activePlayer = &p1;
  Player* opponentPlayer = &p2;
  bool p1Turn = true;
  while (true) {
    // start of turn
    std::cout << "Player ";
    p1Turn ? std::cout << "1 : "
           : std::cout << "2 : ";
    std::cout << activePlayer->getName() << "'s turn." << std::endl;

    // gain 1 magic
    activePlayer->adjustMagic(kStartOfTurnMagic);
    // draw a card
    activePlayer->drawCard();

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
        activePlayer->drawCard();

      } else if (cmd == "discard" && testingMode) {
        int handInd;
        if (currline >> handInd) {
          activePlayer->discard(handInd);
        } else {
          std::cerr << "Error, no hand index given" << std::endl;
        }

      } else if (cmd == "attack") {
        int myMinion;
        int target;
        if (currline >> myMinion) {
          // player checks if myMinion is out of range
          if (currline >> target && currline.peek() == EOF) {
            activePlayer->attackMinion(myMinion, *opponentPlayer, target);
          } else if (currline.eof()) {
            // attacking the other player
            activePlayer->attackPlayer(myMinion, *opponentPlayer);
          } else {
            std::cerr << "Error Invalid input, expected an integer to target"
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
                std::cerr
                    << "Error Invalid input, player and or card targets are "
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
                  activePlayer->playCard(myCard, p1, targetInd);
                } else {  // must be targeting player 2
                  activePlayer->playCard(myCard, p2, targetInd);
                }
              }
            } else {
              std::cerr << "Error Invalid input, expected an integer"
                        << std::endl;
            }
          } else if (currline.eof()) {
            activePlayer->playCard(myCard);
          } else {
            std::cerr << "Error Invalid input, expected an integer"
                      << std::endl;
          }
        } else {
          std::cerr << "Error, no card index give" << std::endl;
        }

      } else if (cmd == "use") {
        // do later since abilities aren't done yet
      } else if (cmd == "describe") {
        // todo
      } else if (cmd == "hand") {
        printHand(*activePlayer);
      } else if (cmd == "board") {
        printBoard(*activePlayer, *opponentPlayer);
      } else {
        std::cerr << "Error: Command not recognized" << std::endl;
      }
    }

    // end of turn
    // activate end of turn triggers (do later)
    //...
    std::swap(activePlayer, opponentPlayer);
    p1Turn = not(p1Turn);
  }
}
