#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
#include <string>
#include <vector>

#include "Subject.h"

class Card;
class Minion;
class Ritual;

class Player : public Subject {
  std::string name;
  int life;
  int magic;

  std::vector<std::unique_ptr<Card>> deck;
  std::vector<std::unique_ptr<Card>> hand;
  std::vector<std::unique_ptr<Minion>> board;
  std::unique_ptr<Ritual> ritual;
  std::vector<std::unique_ptr<Minion>> graveyard;

  bool boundIndex(int index, int lower, int upper,
                  const std::string& indexName) const;

  bool canAfford(int cost) const;

 public:
  Player(const std::string& name, std::vector<std::unique_ptr<Card>> deck);

  void playCard(int handIndex);
  // target index is 0 for ritual, 1-5 for minions
  void playCard(int handIndex, Player& targetPlayer, int targetIndex);
  void drawCard();
  void discard(int handIndex);
  void attackMinion(int boardIndex, Player& targetPlayer, int targetIndex);
  void attackPlayer(int boardIndex, Player& targetPlayer);
  void use(int boardIndex, Player& inactivePlayer);
  void use(int boardIndex, Player& targetPlayer, int targetIndex);

  int getCost(int handIndex) const;
  int boardCost(int boardIndex) const;

  const std::string& getName() const;
  int getLife() const;
  int getMagic() const;

  void adjustLife(int amount);
  void adjustMagic(int amount);

  void setBoard(int index, std::unique_ptr<Card> card);

  std::vector<std::unique_ptr<Minion>>& getHand() const;
  std::vector<std::unique_ptr<Minion>>& getBoard() const;  // goes from 1-5
  std::unique_ptr<Ritual>& getRitual() const;
};

#endif
