#include "Game.h"
#include <iostream>
#include "SDLGraphics.h"
#include "RenderCode.h"
#include "SDL.h"
#include "SDL2/SDL_image.h"


Game::Game(SDLGraphics& arGraphics)
  : mrGraphics(arGraphics) 
{
    mpRenderer = mrGraphics.getRenderer();
    image = mrGraphics.loadTexture("images/spritesheet.png");
    button = mrGraphics.loadTexture("images/button.png");
}


void Game::play()
{
    bool quit = false;
    while (!quit) 
    {
        quit = handleEvents();
        renderScene();
    }
}

bool Game::handleEvents()
{
    bool quit = false;
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            quit = true;
        if (e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
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
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int xis = e.motion.x;
            std::cout << "xis " << xis << std::endl;
            int xTiles = 70;

            int col = xis / xTiles;
            mBoard.addPeice(RED,  (enum ColumnName)col);
        }
    }
    return quit;
}
void Game::renderScene(){
        //Render the scene
        SDL_RenderClear(mpRenderer);
        renderBoard();
         
        SDL_RenderPresent(mpRenderer);
}

void Game::renderColumn(enum ColumnName column) {
    int columnIdx =  column;

    int xTiles = 70;
    for (int level = 0; level < Column::MaxHeight; ++level) {
        Peice piece = mBoard.getPositionStatus(column, level);
        
        int x = columnIdx * xTiles;
        int y = Column::MaxHeight*xTiles - (xTiles*level);
        //std::cout << "Render column " << columnIdx << " x,y" << x << ", " << y << std::endl;
        if (piece == RED) 
            renderTexture(button, mpRenderer, x , y);
    }
}

void Game::renderBoard() {
    // Render the columns starting at the first on the left.
    renderColumn(COLUMN0);
    renderColumn(COLUMN1);
    renderColumn(COLUMN2);
    renderColumn(COLUMN3);
    renderColumn(COLUMN4);
    renderColumn(COLUMN5);
    renderColumn(COLUMN6);
}
