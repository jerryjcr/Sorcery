#include "GraphicalDisplay.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <vector>

#include "Enchantment.h"
#include "Minion.h"
#include "Player.h"
#include "Ritual.h"

const std::string kBackgroundPath = "src/assets/img/background.png";

const std::vector<std::string> kCardNames = {
    "Air Elemental",   "Apprentice Summoner",
    "Aura of Power",   "Banish",
    "Blizzard",        "Bone Golem",
    "Dark Ritual",     "Disenchant",
    "Earth Elemental", "Enrage",
    "Fire Elemental",  "Giant Strength",
    "Haste",           "Magic Fatigue",
    "Master Summoner", "Novice Pyromancer",
    "Potion Seller",   "Raise Dead",
    "Recharge",        "Silence",
    "Standstill",      "Unsummon"};

const std::string kImageDirectory = "src/assets/img/";

const std::string kTitle = "Sorcery";

const int kLogicalWidth = 1600;
const int kLogicalHeight = 900;

const int kWindowWidth = 1600;
const int kWindowHeight = 900;

const int kCardWidth = 180;
const int kCardHeight = 252;

const int kWidthPadding = 10;
const int kBoardHeightPadding = 30;
const int kHandHeightPadding = 50;
const int kRitualGraveyardPadding = 50;

const int kStatXOffset = 147;
const int kRitualXOffset = 152;
const int kStatYOffset = 227;
const int kAbilityXOffset = 17;
const int kAbilityYOffset = 190;

const int kFontSize = 12;
const int kAbilityFontSize = 10;

const SDL_Color kBlack = {0, 0, 0, 255};
const SDL_Color kWhite = {255, 255, 255, 255};

std::vector<std::string> makeCardPaths(const std::vector<std::string>& names) {
  std::vector<std::string> paths;
  for (const auto& name : names) {
    std::string path = kImageDirectory + name + ".png";
    paths.push_back(path);
  }
  return paths;
}

const std::vector<std::string> kCardPaths = makeCardPaths(kCardNames);

void GraphicalDisplay::initializeMap() {
  for (size_t i = 0; i < kCardNames.size(); i++) {
    cardNameToIndex[kCardNames[i]] = i;
  }
}

void GraphicalDisplay::clear() {
  if (!renderer) {
    std::cerr << "Error: Cannot clear without a renderer." << std::endl;
    return;
  }
  SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
  SDL_RenderClear(renderer.get());
}

void GraphicalDisplay::drawBackground() {
  if (!backgroundTexture) {
    std::cerr << "Error: Null background texture." << std::endl;
    return;
  }

  SDL_Rect destRect(0, 0, kLogicalWidth, kLogicalHeight);

  SDL_RenderCopy(renderer.get(), backgroundTexture.get(), nullptr, &destRect);
}

void GraphicalDisplay::drawCard(Card& card, int x, int y) {
  std::string name = card.getName();

  auto it = cardNameToIndex.find(name);

  if (it == cardNameToIndex.end()) {
    std::cerr << "Error: Could not find card with name " << name << "."
              << std::endl;
    return;
  }

  size_t index = it->second;

  if (!cardTextures[index]) {
    std::cerr << "Error: Null card texture." << std::endl;
    return;
  }

  SDL_Rect destRect(x, y, kCardWidth, kCardHeight);

  SDL_RenderCopy(renderer.get(), cardTextures[index].get(), nullptr, &destRect);

  if (card.getType() == CardType::Enchantment) {
    Enchantment* enchantment(dynamic_cast<Enchantment*>(&card));
    if (enchantment->getParent() != nullptr) {
      drawText(std::to_string(static_cast<Minion&>(card).getAttack()) + "/" +
                   std::to_string(static_cast<Minion&>(card).getDefence()),
               x + kStatXOffset, y + kStatYOffset, kFontSize);
      if ((card.getName() == std::string("Novice Pyromancer") ||
           card.getName() == std::string("Apprentice Summoner") ||
           card.getName() == std::string("Master Summoner"))) {
        drawText(std::to_string(static_cast<Minion&>(card).getAbilityCost()),
                 x + kAbilityXOffset, y + kAbilityYOffset, kFontSize);
      }
    }
  } else if (card.getType() == CardType::Minion) {
    drawText(std::to_string(static_cast<Minion&>(card).getAttack()) + "/" +
                 std::to_string(static_cast<Minion&>(card).getDefence()),
             x + kStatXOffset, y + kStatYOffset, 12);
    if ((card.getName() == std::string("Novice Pyromancer") ||
         card.getName() == std::string("Apprentice Summoner") ||
         card.getName() == std::string("Master Summoner"))) {
      drawText(std::to_string(static_cast<Minion&>(card).getAbilityCost()),
               x + kAbilityXOffset, y + kAbilityYOffset, kAbilityFontSize);
    }
  } else if (card.getType() == CardType::Ritual) {
    drawText(std::to_string(dynamic_cast<Ritual&>(card).getCharges()),
             x + kRitualXOffset, y + kStatYOffset, 12);
  }
}

void GraphicalDisplay::drawText(const std::string& message, int x, int y,
                                int fontSize, bool isBlack) {
  if (!font) {
    std::cerr << "Error: " << TTF_GetError() << std::endl;
    return;
  }

  SDL_Color color;
  if (isBlack) {
    color = kBlack;
  } else {
    color = kWhite;
  }
  std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> textSurface(
      TTF_RenderText_Blended(font.get(), message.c_str(), color),
      SDL_FreeSurface);
  if (!textSurface) {
    std::cerr << "Error rendering text surface: " << TTF_GetError()
              << std::endl;
    return;
  }

  texturePtr textTexture(
      SDL_CreateTextureFromSurface(renderer.get(), textSurface.get()),
      SDL_DestroyTexture);
  if (!textTexture) {
    std::cerr << "Error creating text texture: " << SDL_GetError() << std::endl;
    return;
  }

  SDL_Rect dstRect = {x, y, textSurface->w, textSurface->h};
  SDL_RenderCopy(renderer.get(), textTexture.get(), nullptr, &dstRect);
}

void GraphicalDisplay::present() { SDL_RenderPresent(renderer.get()); }

GraphicalDisplay::GraphicalDisplay()
    : window(nullptr, SDL_DestroyWindow),
      renderer(nullptr, SDL_DestroyRenderer),
      backgroundTexture(nullptr, SDL_DestroyTexture),
      font(TTF_OpenFont("src/assets/fonts/Beleren2016-Bold.ttf", kFontSize),
           TTF_CloseFont) {
  initializeMap();
}

bool GraphicalDisplay::createWindow() {
  window.reset(SDL_CreateWindow(kTitle.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, kWindowWidth,
                                kWindowHeight, SDL_WINDOW_SHOWN));
  if (!window) {
    std::cerr << "Error: " << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}

bool GraphicalDisplay::createRenderer() {
  if (!window) {
    std::cerr << "Error: Cannot create renderer without a window." << std::endl;
    return false;
  }

  renderer.reset(SDL_CreateRenderer(window.get(), -1, 0));

  if (!renderer) {
    std::cerr << "Error: " << SDL_GetError() << std::endl;
    return false;
  }
  SDL_RenderSetLogicalSize(renderer.get(), kLogicalWidth, kLogicalHeight);

  return true;
}

bool GraphicalDisplay::loadTextures() {
  if (!renderer) {
    std::cerr << "Error: Cannot load texture without a renderer." << std::endl;
    return false;
  }

  std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> backgroundSurface(
      IMG_Load(kBackgroundPath.c_str()), SDL_FreeSurface);

  if (!backgroundSurface) {
    std::cerr << "Error: " << SDL_GetError() << std::endl;
    return false;
  }

  texturePtr texture(
      SDL_CreateTextureFromSurface(renderer.get(), backgroundSurface.get()),
      SDL_DestroyTexture);

  backgroundTexture = std::move(texture);

  for (const auto& path : kCardPaths) {
    std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface(
        IMG_Load(path.c_str()), SDL_FreeSurface);

    if (!surface) {
      std::cerr << "Error: " << SDL_GetError() << std::endl;
      return false;
    }

    texturePtr texture(
        SDL_CreateTextureFromSurface(renderer.get(), surface.get()),
        SDL_DestroyTexture);

    cardTextures.emplace_back(std::move(texture));
  }

  return true;
}

void GraphicalDisplay::update(Player& activePlayer, Player& inactivePlayer) {
  clear();
  drawBackground();

  int x = kLogicalWidth / 2 - 3.5 * kCardWidth - 2 * kWidthPadding -
          kRitualGraveyardPadding;
  int y = kBoardHeightPadding;

  if (inactivePlayer.getRitual()) {
    drawCard(*inactivePlayer.getRitual(), x, y);
  }

  x += kCardWidth + kRitualGraveyardPadding;

  for (int i = 0; i < 5; i++) {
    if (i < inactivePlayer.getBoard().size()) {
      std::unique_ptr<Minion>& minion = inactivePlayer.getBoard()[i];
      drawCard(*minion, x, y);
    }
    if (i != 4) {
      x += kCardWidth + kWidthPadding;
    }
  }

  x += kCardWidth + kRitualGraveyardPadding;

  if (!inactivePlayer.getGraveyard().empty()) {
    std::unique_ptr<Minion>& minion = inactivePlayer.getGraveyard().back();
    drawCard(*minion, x, y);
  }

  x = kLogicalWidth / 2 - 3.5 * kCardWidth - 2 * kWidthPadding -
      kRitualGraveyardPadding;
  y += kCardHeight + kBoardHeightPadding;

  if (activePlayer.getRitual()) {
    drawCard(*activePlayer.getRitual(), x, y);
  }

  x += kCardWidth + kRitualGraveyardPadding;

  for (int i = 0; i < 5; i++) {
    if (i < activePlayer.getBoard().size()) {
      std::unique_ptr<Minion>& minion = activePlayer.getBoard()[i];
      drawCard(*minion, x, y);
    }
    if (i != 4) {
      x += kCardWidth + kWidthPadding;
    }
  }

  x += kCardWidth + kRitualGraveyardPadding;

  if (!activePlayer.getGraveyard().empty()) {
    std::unique_ptr<Minion>& minion = activePlayer.getGraveyard().back();
    drawCard(*minion, x, y);
  }

  x = kLogicalWidth / 2 - 2.5 * kCardWidth - 2 * kWidthPadding;
  y += kCardHeight + kHandHeightPadding;

  for (auto& card : activePlayer.getHand()) {
    drawCard(*card, x, y);
    x += kCardWidth + kWidthPadding;
  }

  drawText(activePlayer.getName(), 700, 880, kFontSize, false);

  present();
}
