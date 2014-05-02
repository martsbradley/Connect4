#ifndef CONNECT4GRID_H
#define CONNECT4GRID_H
#include "Board.h"

class SDLGraphics;
class SDL_Texture;
class SDL_Renderer;
class PieceAnimation;
union SDL_Event;

class Connect4Grid {

public:
    Connect4Grid(SDLGraphics& arGraphics);
    ~Connect4Grid();
    void renderBoard();
    void handleEvent(SDL_Event& arEvent);
    void updateGame();
    bool isGameOver();
    void setGameOver(bool aGameOver);
private:
    void renderColumn(enum ColumnName column);
    void renderBoardOutline();
    void renderWinningLine();

    void startAnimation(int col);

    Board mBoard;
    SDL_Texture* mpRedButton;
    SDL_Texture* mpYellowButton;
    SDL_Texture* mpWinningButton;
    SDL_Texture* mpBoardTexture;
    SDLGraphics& mrGraphics;

    SDL_Renderer *mpRenderer;

    PieceAnimation* mpAnimation;
};
#endif // CONNECT4GRID_H
