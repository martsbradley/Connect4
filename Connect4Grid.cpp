#include "SDLGraphics.h"
#include "Connect4Grid.h"
#include "RenderCode.h"
#include "SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

Connect4Grid::Connect4Grid(SDLGraphics& arGraphics)
  : mrGraphics(arGraphics) 
{
    //image = mrGraphics.loadTexture("images/spritesheet.png");
    mpRenderer = mrGraphics.getRenderer();
    mpRedButton = mrGraphics.loadTexture("images/redbutton.png");
    mpYellowButton =  mrGraphics.loadTexture("images/yellowbutton.png");
    nextPeice = RED;
}
Connect4Grid::~Connect4Grid() {
}

void Connect4Grid::renderBoard()
{
    // Render the columns starting at the first on the left.
    renderColumn(COLUMN0);
    renderColumn(COLUMN1);
    renderColumn(COLUMN2);
    renderColumn(COLUMN3);
    renderColumn(COLUMN4);
    renderColumn(COLUMN5);
    renderColumn(COLUMN6);
}
void Connect4Grid::renderColumn(enum ColumnName column)
{
    int columnIdx =  column;

    int xTiles = 70;
    for (int level = 0; level < Column::MaxHeight; ++level) {
        Peice piece = mBoard.getPositionStatus(column, level);
        
        int x = columnIdx * xTiles;
        int y = Column::MaxHeight*xTiles - (xTiles*level);
        //std::cout << "Render column " << columnIdx << " x,y" << x << ", " << y << std::endl;
        if (piece == RED) 
            renderTexture(mpRedButton, mpRenderer, x , y);
        else if (piece == YELLOW)
            renderTexture(mpYellowButton, mpRenderer, x , y);
    }
}

void Connect4Grid::handleEvent(SDL_Event& arEvent) 
{
    if (arEvent.type == SDL_KEYDOWN) {
        switch(arEvent.key.keysym.sym) {
            case SDLK_1:
                break;
            case SDLK_2:
                break;
            case SDLK_3:
                break;
            case SDLK_4:
                break;
            default: // nothing
                ;
        }
    }

    if (arEvent.type == SDL_MOUSEBUTTONDOWN) {
        int xis = arEvent.motion.x;
        std::cout << "xis " << xis << std::endl;
        int xTiles = 70;

        unsigned int col = xis / xTiles;
        if (col <= COLUMN6)
        {
            mBoard.addPeice(nextPeice, (enum ColumnName)col);
            if (nextPeice == RED)
               nextPeice = YELLOW;
            else 
               nextPeice = RED;
        }
    }
}
