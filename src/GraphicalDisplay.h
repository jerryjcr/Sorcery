#ifndef GRAPHICALDISPLAY_H_
#define GRAPHICALDISPLAY_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <memory>
#include <vector>

class GraphicalDisplay {
  using windowPtr = std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>;
  windowPtr window;

  using rendererPtr = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>;
  rendererPtr renderer;

  using texturePtr = std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)>;
  texturePtr backgroundTexture;
  std::vector<texturePtr> cardTextures;

  void clear();

  void drawBackground();

  void drawCard(size_t index, int x, int y, int w, int h);

  void present();

 public:
  GraphicalDisplay();

  ~GraphicalDisplay();

  bool createWindow(const std::string& title, int width, int height);

  bool createRenderer();

  bool loadTextures(const std::string& backgroundPath, const std::vector<std::string>& cardPaths);

  void update();
};

#endif
