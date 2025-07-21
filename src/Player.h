#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
#include <string>

#include "Subject.h"

class Card;
class Minion;
class Ritual;

const int kInitialLife = 20;
const int kInitialMagic = 3;

class Player : public Subject {
  std::string playerName;
  int life;
  int magic;

  std::vector<std::unique_ptr<Card>> deck;
  std::vector<std::unique_ptr<Card>> hand;
  std::vector<std::unique_ptr<Minion>> board;
  std::vector<std::unique_ptr<Ritual>> ritual;
  std::vector<std::unique_ptr<Minion>> graveyard;

 public:
  Player(std::string name, std::vector<std::unique_ptr<Card>> deck,
         int life = kInitialLife, int magic = kInitialMagic);

  void playCard(int handIndex);
  void playCard(int handIndex, Player& targetPlayer, int targetIndex);
  void drawCard();
  void discard(int handIndex);
  void attackMinion(int boardIndex, Player& targetPlayer, int targetIndex);
  void use(int boardIndex);
  void describeHand() const;
  void describeBoard() const;

  int getLife() const;
  int getMagic() const;

  int adjustLife(int amount);
  int adjustMagic(int amount);

  void setBoard(int index, std::unique_ptr<Card> card);

  void moveCard(std::vector<std::unique_ptr<Card>>& oldDeck,
                std::vector<std::unique_ptr<Card>>& newDeck,
                int index);  // moves oldDeck[index] to newDeck
};

#endif
