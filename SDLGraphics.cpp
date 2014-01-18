#include "SDLGraphics.h"
#include <stdexcept>
#include <iostream>
//#include <iterator>

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

