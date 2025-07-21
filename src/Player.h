#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
#include <string>
#include <vector>

#include "Subject.h"

class Card;
class Minion;
class Ritual;

const int kInitialLife = 20;
const int kInitialMagic = 3;

class Player : public Subject {
  std::string playerName;

  std::vector<std::unique_ptr<Card>> deck;
  std::vector<std::unique_ptr<Card>> hand;
  std::vector<std::unique_ptr<Minion>> board;
  std::unique_ptr<Ritual> ritual;
  std::vector<std::unique_ptr<Minion>> graveyard;

  int life;
  int magic;

 public:
  Player(std::string name, std::vector<std::unique_ptr<Card>> deck,
         int life = kInitialLife, int magic = kInitialMagic);

  void playCard(int handIndex);
  // target index is 0 for ritual, 1-5 for minions
  void playCard(int handIndex, Player& targetPlayer, int targetIndex);
  void drawCard();
  void discard(int handIndex);
  void attackMinion(int boardIndex, Player& targetPlayer, int targetIndex);
  void attackPlayer(int boardIndex, Player& targetPlayer);
  void use(int boardIndex);
  void describeHand() const;
  void describeBoard() const;

  int getLife() const;
  int getMagic() const;

  void adjustLife(int amount);
  void adjustMagic(int amount);

  void setBoard(int index, std::unique_ptr<Card> card);

  std::unique_ptr<Ritual>& getRitual() const;
  std::unique_ptr<Minion>& getBoard(int index) const; //goes from 1-5

  void moveCard(std::vector<std::unique_ptr<Card>>& oldDeck,
                std::vector<std::unique_ptr<Card>>& newDeck,
                int index);  // moves oldDeck[index] to newDeck
};

#endif
