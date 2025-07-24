#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Card.h"
#include "Database.h"
#include "GraphicalDisplay.h"
#include "Minion.h"
#include "Player.h"
#include "Ritual.h"
#include "TextUI.h"

const int kStartOfTurnMagic = 1;
const int kMaxNameLength = 28;
const int kStartingHandSize = 5;
const std::string kDefaultDeck = "assets/text/default.txt";
const std::string kBackgroundPath = "assets/img/background.png";
const std::vector<std::string> kCardPaths = {"assets/img/Master Summoner.png",
                                             "assets/img/Earth Elemental.png"};

int main(int argc, char* argv[]) {
  // processing command line args
  bool testingMode = false;
  bool graphicsMode = false;

  std::string decklist1 = kDefaultDeck;
  std::string decklist2 = kDefaultDeck;
  std::fstream fileIn;

  for (int i = 1; i < argc; i++) {
    std::string cmd = argv[i];

    if (cmd == "-deck1") {
      if (i + 1 >= argc) {
        std::cerr
            << "Error: No filename given for deck 1. Using default.txt instead."
            << std::endl;
        decklist1 = kDefaultDeck;
      } else {
        i++;
        decklist1 = argv[i];
      }
    } else if (cmd == "-deck2") {
      if (i + 1 >= argc) {
        std::cerr
            << "Error: No filename given for deck 2. Using default.txt instead."
            << std::endl;
        decklist2 = kDefaultDeck;
      } else {
        i++;
        decklist2 = argv[i];
      }
    } else if (cmd == "-init") {
      if (i + 1 >= argc) {
        std::cerr << "Error: No filename given for taking input. Reading from "
                     "stdin instead."
                  << std::endl;
        fileIn = std::fstream{};
      } else {
        i++;
        fileIn = std::fstream{argv[i]};
      }
    } else if (cmd == "-testing") {
      testingMode = true;
    } else if (cmd == "-graphics") {
      graphicsMode = true;
    }
  }

  std::unique_ptr<GraphicalDisplay> display;

  if (graphicsMode) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      std::cerr << "Error: " << SDL_GetError() << std::endl;
      return 1;
    }

    display = std::make_unique<GraphicalDisplay>();
    display->createWindow("Sorcery", 1280, 960);
    display->createRenderer();
    display->loadTextures(kBackgroundPath, kCardPaths);
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

  // intializing decks
  std::string name1, name2;
  while (true) {
    if (!std::getline(fileIn, name1)) {
      std::getline(std::cin, name1);
    }
    if (name1.length() > kMaxNameLength) {
      std::cerr << "Invalid input: Name too long, please enter a shorter name."
                << std::endl;
    } else {
      break;
    }
  }
  while (true) {
    if (!std::getline(fileIn, name2)) {
      std::getline(std::cin, name2);
    }
    if (name2.length() > kMaxNameLength) {
      std::cerr << "Invalid input: Name too long, please enter a shorter name."
                << std::endl;
    } else {
      break;
    }
  }

  Player p1{name1, std::move(deck1)};
  Player p2{name2, std::move(deck2)};

  /*
  p1.shuffleDeck();
  p2.shuffleDeck();
  */

  // drawing starting hands
  for (int i = 0; i < kStartingHandSize; i++) {
    p1.drawCard();
    p2.drawCard();
  }

  Player* activePlayer = &p1;
  Player* opponentPlayer = &p2;
  bool p1Turn = true;
  while (true) {
    // start of turn
    std::cout << "Player ";
    p1Turn ? std::cout << "1 : " : std::cout << "2 : ";
    std::cout << activePlayer->getName() << "'s turn." << std::endl;

    // gain 1 magic
    activePlayer->adjustMagic(kStartOfTurnMagic);
    // draw a card
    activePlayer->drawCard();

    activePlayer->resetBoardActions();

    // start of turn triggers
    activePlayer->triggerBoard(*opponentPlayer, TriggerType::MyStartOfTurn);
    opponentPlayer->triggerBoard(*activePlayer,
                                 TriggerType::OpponentStartOfTurn);

    // "action phase"
    while (true) {
      // checking if someone won the game
      if (p1.getLife() < 1 && p2.getLife() < 1) {
        printBoard(*activePlayer, *opponentPlayer);
        std::cout << "Both players have fallen!" << std::endl;
        std::cout << "The game ends in a draw." << std::endl;
        return 0;
      } else if (p1.getLife() < 1) {
        printBoard(*activePlayer, *opponentPlayer);
        std::cout << p1.getName() << " has fallen in combat!" << std::endl;
        std::cout << p2.getName() << " wins!" << std::endl;
        return 0;
      } else if (p2.getLife() < 1) {
        printBoard(*activePlayer, *opponentPlayer);
        std::cout << p2.getName() << " has fallen in combat!" << std::endl;
        std::cout << p1.getName() << " wins!" << std::endl;
        return 0;
      }

      // checking if anyone died
      activePlayer->checkForDeaths(*opponentPlayer);
      opponentPlayer->checkForDeaths(*activePlayer);

      // update screen
      display->update();

      // taking input either from file or stdin
      std::string cmd;
      if (!std::getline(fileIn, cmd)) {
        std::getline(std::cin, cmd);
      }
      std::stringstream currline{cmd};
      cmd.clear();
      currline >> cmd;

      if (cmd == "help") {
        std::fstream help("assets/text/help.txt");
        std::string helpLine;
        while (std::getline(help, helpLine)) {
          std::cout << helpLine << std::endl;
        }
        help.close();

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
          std::cerr << "Invalid input: No hand index given." << std::endl;
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
            std::cerr << "Invalid input: Wrong arguments." << std::endl;
          }
        } else {
          std::cerr << "Invalid input: No minion index given." << std::endl;
        }

      } else if (cmd == "play" || cmd == "use") {
        int myCard;
        int targetPlayer;
        char targetCard;
        bool isRitual = false;
        if (currline >> myCard) {
          if (currline >> targetPlayer) {
            if (currline >> targetCard && currline.peek() == EOF) {
              if ((targetPlayer != 1 && targetPlayer != 2) ||
                  (targetCard != 'r' &&
                   (targetCard < '1' || targetCard > '5'))) {
                std::cerr << "Invalid input: Player and/or card targets are "
                             "out of range."
                          << std::endl;
              } else {
                int targetInd = 0;
                // we all agree that 6 is how you target a ritual
                targetCard == 'r' ? isRitual = true
                                  : targetInd = targetCard - '0';

                // this is weird since the players may forget who player 1 and 2
                // are, perhaps send a message reminding them?
                if (targetPlayer == 1) {
                  if (cmd == "play") {
                    activePlayer->playCard(myCard, p1, targetInd, p2, isRitual);
                  } else {
                    activePlayer->use(myCard, p1, targetInd, p2, isRitual);
                  }
                } else {  // must be targeting player 2
                  if (cmd == "play")
                    activePlayer->playCard(myCard, p2, targetInd, p1, isRitual);
                  else
                    activePlayer->use(myCard, p2, targetInd, p1, isRitual);
                }
              }
            } else {
              std::cerr << "Invalid input: Expected an integer." << std::endl;
            }
          } else if (currline.eof()) {
            if (cmd == "play") {
              activePlayer->playCard(myCard, *opponentPlayer);
            } else {
              activePlayer->use(myCard, *opponentPlayer);
            }
          } else {
            std::cerr << "Invalid input: Expected an integer." << std::endl;
          }
        } else {
          std::cerr << "Invalid input: No card index given." << std::endl;
        }
      } else if (cmd == "inspect") {
        int boardInd;
        if (currline >> boardInd && currline.peek() == EOF) {
          if (activePlayer->getBoard().size() > boardInd) {
            inspectCard(*activePlayer->getBoard()[boardInd - 1]);
          } else {
            std::cerr << "Invalid input: given index is out of bounds."
                      << std::endl;
          }
        } else {
          std::cerr << "Invalid input: Expected a single integer" << std::endl;
        }
      } else if (cmd == "hand") {
        printHand(*activePlayer);
      } else if (cmd == "board") {
        printBoard(*activePlayer, *opponentPlayer);
      } else {
        std::cerr << "Invalid input: Command not recognized." << std::endl;
      }
    }

    // end of turn
    activePlayer->triggerBoard(*opponentPlayer, TriggerType::MyEndOfTurn);
    opponentPlayer->triggerBoard(*activePlayer, TriggerType::OpponentEndOfTurn);
    std::swap(activePlayer, opponentPlayer);
    p1Turn = not(p1Turn);
  }

  SDL_Quit();
}
