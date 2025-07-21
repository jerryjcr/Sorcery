#include "Player.h"

Player::Player(std::string name, int life, int magic,
               std::vector<std::unique_ptr<Card>> deck)
    : playerName{name}, life{life}, magic{magic}, deck{std::move(deck)} {}

void Player::playCard(int handIndex) {
  // todo
}

void Player::playCard(int handIndex, Player& targetPlayer, int targetIndex) {
  // todo
}

void Player::drawCard() {
  // todo
}

void Player::discard(int handIndex) {
  // todo
}

void Player::attackMinion(int boardIndex, Player& targetPlayer,
                          int targetIndex) {
  // todo
}

void Player::use(int boardIndex) {
  // todo
}

void Player::describeHand() const {
  // todo
}

void Player::describeBoard() const {
  // todo
}

int Player::getLife() const { return life; }

int Player::getMagic() const { return magic; }

int Player::adjustLife(int amount) { life += amount; }

int Player::adjustMagic(int amount) { magic += amount; }

void Player::setBoard(int index, std::unique_ptr<Card> card) {
  // todo
}

void Player::moveCard(std::vector<std::unique_ptr<Card>>& oldDeck,
                      std::vector<std::unique_ptr<Card>>& newDeck, int index) {
  // todo
}
