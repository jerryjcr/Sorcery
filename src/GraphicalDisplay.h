#ifndef GRAPHICALDISPLAY_H_
#define GRAPHICALDISPLAY_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

  void initializeMap();

  void clear();

  void drawBackground();

  void drawCard(const std::string& name, int x, int y, int w, int h);

  void present();

 public:
  GraphicalDisplay();

  bool createWindow(const std::string& title, int width, int height);

  bool createRenderer();

  bool loadTextures();

  void update(Player& activePlayer, Player& inactivePlayer);
};

#endif
