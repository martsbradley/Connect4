#ifndef GAME_H
#define GAME_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class SDLGraphics;
class Connect4Grid;

//  below includes will be removed to subclass
struct SDL_Texture;

#include "Board.h"

class Game {
public:
    Game(SDLGraphics& arGraphics);
    ~Game();
    void play();
    bool handleEvents();
    void renderScene();
private:
    SDLGraphics& mrGraphics;
    SDL_Renderer *mpRenderer;

    Connect4Grid* mpGrid;
};
#endif  // GAME_H
