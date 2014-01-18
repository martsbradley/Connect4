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


private:
    std::list<SDL_Texture*> textures;

    SDL_Window* mpWindow;
    SDL_Renderer* mpRenderer;
};
