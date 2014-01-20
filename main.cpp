#include "SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include "Game.h"
#include "SDLGraphics.h"

//const int SCREEN_WIDTH  = 640;
//const int SCREEN_HEIGHT = 480;
////We'll just be using square tiles for now
//const int TILE_SIZE = 65;






int main(int argc, char** argv){
    SDLGraphics graphics;

    Game game(graphics);   
    game.play();

    return 0;
}
