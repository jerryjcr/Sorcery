#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
#include <string>

#include "Subject.h"

class Card;
class Minion;
class Ritual;

class Player : public Subject {
  std::string playerName;
  int life;
  int magic;

  std::vector<std::unique_ptr<Card>> deck;
  std::vector<std::unique_ptr<Card>> hand;
  // ritual is at index 0, then 1-5 goes from left to right
  std::vector<std::unique_ptr<Card>> board;
  std::vector<std::unique_ptr<Minion>> graveyard;

 public:
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

  void setBoard(
      int index,
      std::unique_ptr<Card> card);  // note index 0 is for ritual, index 1-5
                                    // goes from left to right

  void moveCard(std::vector<std::unique_ptr<Card>>& oldDeck,
                std::vector<std::unique_ptr<Card>>& newDeck,
                int index);  // moves oldDeck[index] to newDeck
};

#endif
