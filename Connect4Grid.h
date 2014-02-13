#ifndef CONNECT4GRID_H
#define CONNECT4GRID_H
#include "Board.h"

class SDLGraphics;
class SDL_Texture;
class SDL_Renderer;
class PieceAnimation;
union SDL_Event;

//  struct NextPiece {

//     NextPiece() :
//        next(RED),
//        pButton(0)
//     {
//     }

//     NextPiece(Piece p, SDL_Texture*t) :
//        next(p),
//        pButton(t)
//     {
//     }

//     Piece next;
//     SDL_Texture* pButton;
//  };

class Connect4Grid {

public:
    Connect4Grid(SDLGraphics& arGraphics);
    ~Connect4Grid();
//  below members will be removed to subclass
    void renderBoard();

    void handleEvent(SDL_Event& arEvent);
private:
    void renderColumn(enum ColumnName column);
    void renderBoardOutline();

    void startAnimation(int col);

    Board mBoard;

    //SDL_Texture* image;
    SDL_Texture* mpRedButton;
    SDL_Texture* mpYellowButton;
    SDL_Texture* mpBoardTexture;
    SDLGraphics& mrGraphics;

    SDL_Renderer *mpRenderer;
    //struct NextPiece nextPiece;

    PieceAnimation* mpAnimation;
};
#endif // CONNECT4GRID_H
