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

 public:
  GraphicalDisplay();

  bool createWindow(const std::string& title, int width, int height);

  bool createRenderer();

  bool loadBackgroundTexture(const std::string& filePath);

  bool loadCardTextures(const std::vector<std::string>& filePaths);

  bool isInitialized() const;
};

#endif
