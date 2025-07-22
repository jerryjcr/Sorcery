#include "Player.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Card.h"
#include "Minion.h"
#include "Ritual.h"
#include "Spell.h"

const int kInitialLife = 20;
const int kInitialMagic = 3;

Player::Player(const std::string& name, std::vector<std::unique_ptr<Card>> deck)
    : playerName{name},
      deck{std::move(deck)},
      life{kInitialLife},
      magic{kInitialMagic} {}

void Player::playCard(int handIndex) {
  if (handIndex < 0 || handIndex >= static_cast<int>(hand.size())) return;

  std::unique_ptr<Card>& card = hand[handIndex];
  int cost = card->getCost();
  if (magic < cost) {
    std::cerr << "Not enough magic to play this card." << std::endl;
    return;
  }

  // detect the type of card by casting to the appropriate pointer
  if (Minion* minionRawPtr = dynamic_cast<Minion*>(card.get())) {
    if (board.size() >= 5) {
      std::cerr << "Board is full." << std::endl;
      return;
    }
    std::unique_ptr<Minion> minion(static_cast<Minion*>(card.release()));
    board.push_back(std::move(minion));
  } else if (Ritual* ritualRawPtr = dynamic_cast<Ritual*>(card.get())) {
    std::unique_ptr<Ritual> newRitual(static_cast<Ritual*>(card.release()));
    ritual = std::move(newRitual);
  } else if (Spell* spellRawPtr = dynamic_cast<Spell*>(card.get());
             spellRawPtr && !spellRawPtr->requiresTarget()) {
    std::unique_ptr<Spell> spell(static_cast<Spell*>(card.release()));
    spell->useSpell();  // call the version of the method with no target
  } else {
    std::cerr << "Must specify target player and index to play this card."
              << std::endl;
    return;
  }

  magic -= cost;
  hand.erase(hand.begin() + handIndex);
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

void Player::attackPlayer(int boardIndex, Player& targetPlayer) {
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

void Player::adjustLife(int amount) { life += amount; }

void Player::adjustMagic(int amount) { magic += amount; }

void Player::setBoard(int index, std::unique_ptr<Card> card) {
  // todo
}

void Player::moveCard(std::vector<std::unique_ptr<Card>>& oldDeck,
                      std::vector<std::unique_ptr<Card>>& newDeck, int index) {
  // todo
}
