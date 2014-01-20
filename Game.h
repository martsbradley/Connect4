#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include "SDL2/SDL_image.h"

class SDLGraphics;

//  below includes will be removed to subclass
struct SDL_Texture;

#include "Board.h"

class Game {
public:
    Game(SDLGraphics& arGraphics);
    void play();
    bool handleEvents();
    void renderScene();
private:
    SDLGraphics& mrGraphics;
    SDL_Renderer *mpRenderer;


//  below members will be removed to subclass
    void renderBoard();
    void renderColumn(enum ColumnName column);

    Board mBoard;
    SDL_Texture* image;
    SDL_Texture* button;
};
#endif  // GAME_H
