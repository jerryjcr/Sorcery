#ifndef GRAPHICALDISPLAY_H_
#define GRAPHICALDISPLAY_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Player.h"

class GraphicalDisplay {
  using windowPtr = std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>;
  windowPtr window;

  using rendererPtr = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>;
  rendererPtr renderer;

  using texturePtr = std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)>;
  texturePtr backgroundTexture;
  std::vector<texturePtr> cardTextures;

  std::unordered_map<std::string, size_t> cardNameToIndex;

  using fontPtr = std::unique_ptr<TTF_Font, void (*)(TTF_Font* font)>;
  fontPtr font;

  void initializeMap();

  void initializeFont();

  void clear();

  void drawBackground();

  void drawCard(Card& card, int x, int y);

  void drawText(const std::string& message, int x, int y, int fontSize,
                SDL_Color color = {255, 255, 255, 255});

  void present();

 public:
  GraphicalDisplay();

  bool createWindow();

  bool createRenderer();

  bool loadTextures();

  void update(Player& activePlayer, Player& inactivePlayer);
};

#endif
