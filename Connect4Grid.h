#ifndef CONNECT4GRID_H
#define CONNECT4GRID_H
#include "Board.h"

class SDLGraphics;
class SDL_Texture;
class SDL_Renderer;
union SDL_Event;

class Connect4Grid {

public:
    Connect4Grid(SDLGraphics& arGraphics);
    ~Connect4Grid();
//  below members will be removed to subclass
    void renderBoard();

    void handleEvent(SDL_Event& arEvent);
private:
    void renderColumn(enum ColumnName column);

    Board mBoard;

    //SDL_Texture* image;
    SDL_Texture* mpRedButton;
    SDL_Texture* mpYellowButton;
    SDLGraphics& mrGraphics;

    SDL_Renderer *mpRenderer;
    Peice nextPeice;
};
#endif // CONNECT4GRID_H
