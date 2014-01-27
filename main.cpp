#include "SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include "Game.h"
#include "SDLGraphics.h"




int main(int argc, char** argv){
    SDLGraphics graphics;

    Game game(graphics);   
    game.play();

    return 0;
}
