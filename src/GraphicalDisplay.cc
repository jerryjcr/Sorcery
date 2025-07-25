#include "GraphicalDisplay.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <vector>

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

void GraphicalDisplay::drawCard(const std::string& name, int x, int y, int w,
                                int h) {
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

  SDL_Rect destRect(x, y, w, h);

  SDL_RenderCopy(renderer.get(), cardTextures[index].get(), nullptr, &destRect);
}

void GraphicalDisplay::present() { SDL_RenderPresent(renderer.get()); }

GraphicalDisplay::GraphicalDisplay()
    : window(nullptr, SDL_DestroyWindow),
      renderer(nullptr, SDL_DestroyRenderer),
      backgroundTexture(nullptr, SDL_DestroyTexture) {
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

  SDL_Texture* rawTexture =
      SDL_CreateTextureFromSurface(renderer.get(), backgroundSurface.get());

  if (!rawTexture) {
    std::cerr << "Error: " << SDL_GetError() << std::endl;
    return false;
  }

  texturePtr texture(rawTexture, SDL_DestroyTexture);

  backgroundTexture = std::move(texture);

  for (const auto& path : kCardPaths) {
    std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface(
        IMG_Load(path.c_str()), SDL_FreeSurface);

    if (!surface) {
      std::cerr << "Error: " << SDL_GetError() << std::endl;
      return false;
    }

    SDL_Texture* rawTexture =
        SDL_CreateTextureFromSurface(renderer.get(), surface.get());

    if (!rawTexture) {
      std::cerr << "Error: " << SDL_GetError() << std::endl;
      return false;
    }

    texturePtr texture(rawTexture, SDL_DestroyTexture);

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
    drawCard(inactivePlayer.getRitual()->getName(), x, y, kCardWidth,
             kCardHeight);
  }

  x += kCardWidth + kRitualGraveyardPadding;

  for (auto& minion : inactivePlayer.getBoard()) {
    drawCard(minion->getName(), x, y, kCardWidth, kCardHeight);
    x += kCardWidth + kWidthPadding;
  }

  x = kLogicalWidth / 2 - 3.5 * kCardWidth - 2 * kWidthPadding -
      kRitualGraveyardPadding;
  y += kCardHeight + kBoardHeightPadding;

  if (activePlayer.getRitual()) {
    drawCard(activePlayer.getRitual()->getName(), x, y, kCardWidth,
             kCardHeight);
  }

  x += kCardWidth + kRitualGraveyardPadding;

  for (auto& minion : activePlayer.getBoard()) {
    drawCard(minion->getName(), x, y, kCardWidth, kCardHeight);
    x += kCardWidth + kWidthPadding;
  }

  x = kLogicalWidth / 2 - 2.5 * kCardWidth - 2 * kWidthPadding;
  y += kCardHeight + kHandHeightPadding;

  for (auto& minion : activePlayer.getHand()) {
    drawCard(minion->getName(), x, y, kCardWidth, kCardHeight);
    x += kCardWidth + kWidthPadding;
  }
}
