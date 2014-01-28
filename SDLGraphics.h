#ifndef SDLGRAPHICS_H
#define SDLGRAPHICS_H
#include "SDL.h"
#include "SDL2/SDL_image.h"
#include <list>
#include <string>

class SDLGraphics {
public:
    SDLGraphics();
    ~SDLGraphics();
    SDL_Renderer* getRenderer();

    SDL_Texture* loadTexture(const std::string& arName);

    SDL_Texture* loadFromFile(const std::string& arFileName);


private:
    std::list<SDL_Texture*> textures;

    SDL_Window* mpWindow;
    SDL_Renderer* mpRenderer;
};
#endif //SDLGRAPHICS_H
