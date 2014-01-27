#include "Game.h"
#include <iostream>
#include "SDLGraphics.h"
#include "RenderCode.h"
#include "SDL.h"
#include "SDL2/SDL_image.h"
#include "Connect4Grid.h"


Game::Game(SDLGraphics& arGraphics)
  : mrGraphics(arGraphics) 
{
    mpRenderer = mrGraphics.getRenderer();
    mpGrid = new Connect4Grid(mrGraphics);
}

Game::~Game() {
    delete mpGrid;
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
        else {
            mpGrid->handleEvent(e);
        }
    }
    return quit;
}
void Game::renderScene(){
        //Render the scene
        SDL_RenderClear(mpRenderer);
        mpGrid->renderBoard();
         
        SDL_RenderPresent(mpRenderer);
}

