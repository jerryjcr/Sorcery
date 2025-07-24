#ifndef GRAPHICALDISPLAY_H_
#define GRAPHICALDISPLAY_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <memory>

class GraphicalDisplay {
  using windowPtr = std::unique_ptr<SDL_Window*, void (*)(SDL_Window*)>;
  windowPtr window(SDL_CreateWindow("Sorcery", SDL_WINDOWPODS_CENTERED,
                                    SD_WINDOWPOS_CENTERED, 1280, 960),
                   SDL_DestroyWindow);
};

#endif
