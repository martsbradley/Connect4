#include "SDLGraphics.h"
#include "SDL.h"
#include "SDL2/SDL_image.h"
#include <stdexcept>
#include <iostream>
//#include <iterator>
  /**
  * Log an SDL error with some error message to the output stream of our choice
  * @param os The output stream to write the message too
  * @param msg The error message to write, format will be msg error: SDL_GetError()
  */
  void logSDLError(std::ostream &os, const std::string &msg){
      os << msg << " error: " << SDL_GetError() << std::endl;
  }

  /**
  * Loads an image into a texture on the rendering device
  * @param file The image file to load
  * @param ren The renderer to load the texture onto
  * @return the loaded texture, or nullptr if something went wrong.
  */
static SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == 0)     
        logSDLError(std::cout, "LoadTexture");
    return texture;
}

SDLGraphics::SDLGraphics()
 : mpWindow(0),
   mpRenderer(0)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        std::cout << SDL_GetError() << std::endl;
        throw std::logic_error(SDL_GetError());
    }


    mpWindow = SDL_CreateWindow("Hello World!", 100, 100, 600, 500, SDL_WINDOW_SHOWN);
    if (mpWindow == 0){
        std::cout << SDL_GetError() << std::endl;
        throw std::logic_error(SDL_GetError());
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
        std::cout << SDL_GetError() << std::endl;
        throw std::logic_error(SDL_GetError());
    }
}

SDLGraphics::~SDLGraphics() {

    std::list<SDL_Texture*>::iterator it;

    for (it = textures.begin(); it != textures.end() ; it++) {
        SDL_DestroyTexture(*it);
    }

    SDL_DestroyRenderer(mpRenderer);
    SDL_DestroyWindow(mpWindow);
    SDL_Quit();
}

SDL_Renderer* SDLGraphics::getRenderer() {

    if (mpRenderer != 0){
        return mpRenderer;
    }

    mpRenderer= SDL_CreateRenderer(mpWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mpRenderer == 0){
        std::cout << SDL_GetError() << std::endl;
        throw std::logic_error(SDL_GetError());
    }
    return mpRenderer;
}

SDL_Texture* SDLGraphics::loadTexture(const std::string& arFileName) {
    SDL_Texture *texture = IMG_LoadTexture(mpRenderer, arFileName.c_str());
    if (texture == 0) {
        throw std::logic_error("Unable to load Texture");
    }

    textures.push_back(texture);
    return texture;
}
