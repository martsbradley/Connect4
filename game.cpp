#include "SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include "Board.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
//We'll just be using square tiles for now
const int TILE_SIZE = 65;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message too
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
    os << msg << " error: " << SDL_GetError() << std::endl;
}

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == 0)     
        logSDLError(std::cout, "LoadTexture");
    return texture;
}










/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw too
* @param x The x coordinate to draw too
* @param y The y coordinate to draw too
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,int w, int h){
    //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, NULL, &dst);
}
/**
* Draw an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired
* @param tex The source texture we want to draw
* @param rend The renderer we want to draw too
* @param dst The destination rectangle to render the texture too
* @param clip The sub-section of the texture to draw (clipping rect)
*       default of nullptr draws the entire texture
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst,
                   SDL_Rect *clip = 0)
{
    SDL_RenderCopy(ren, tex, clip, &dst);
}
/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height and taking a clip of the texture if desired
* If a clip is passed, the clip's width and height will be used instead of
*   the texture's
* @param tex The source texture we want to draw
* @param rend The renderer we want to draw too
* @param x The x coordinate to draw too
* @param y The y coordinate to draw too
* @param clip The sub-section of the texture to draw (clipping rect)
*       default of nullptr draws the entire texture
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,
                   SDL_Rect *clip = 0)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != 0){
        dst.w = clip->w;
        dst.h = clip->h;
    }
    else {
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    }

    renderTexture(tex, ren, dst, clip);
}

void renderColumn(SDL_Renderer* apRen, enum ColumnName column, Board& arBoard, SDL_Texture* apButton) {
    int columnIdx =  column;

    int xTiles = 70;
    for (int level = 0; level < Column::MaxHeight; ++level) {
        Peice piece = arBoard.getPositionStatus(column, level);
        
        int x = columnIdx * xTiles;
        int y = Column::MaxHeight*xTiles - (xTiles*level);
        //std::cout << "Render column " << columnIdx << " x,y" << x << ", " << y << std::endl;
        if (piece == RED) 
            renderTexture(apButton, apRen, x , y );//, TILE_SIZE, TILE_SIZE);
    }
}
void renderBoard(SDL_Renderer* apRen, Board& arBoard, SDL_Texture* apButton) {
    // Render the columns starting at the first on the left.
    renderColumn(apRen, COLUMN0, arBoard, apButton);
    renderColumn(apRen, COLUMN1, arBoard, apButton);
    renderColumn(apRen, COLUMN2, arBoard, apButton);
    renderColumn(apRen, COLUMN3, arBoard, apButton);
    renderColumn(apRen, COLUMN4, arBoard, apButton);
    renderColumn(apRen, COLUMN5, arBoard, apButton);
    renderColumn(apRen, COLUMN6, arBoard, apButton);
}

int main(int argc, char** argv){
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }


    SDL_Window *win = 0;
    win = SDL_CreateWindow("Hello World!", 100, 100, 600, 500, SDL_WINDOW_SHOWN);
    if (win == 0){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
        logSDLError(std::cout, "IMG_Init");
        return 1;
    }


    SDL_Renderer *renderer = 0;
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == 0){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Texture *image = loadTexture("images/spritesheet.png", renderer);
    SDL_Texture *button = loadTexture("images/button.png", renderer);

    if (image == 0 || button == 0)
        return 4;

    SDL_RenderClear(renderer);


    SDL_RenderPresent(renderer);
    //Our event structure
    SDL_Event e;
    bool quit = false;
    Board board;

    while (!quit) {
        while (SDL_PollEvent(&e)){
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
                board.addPeice(RED,  (enum ColumnName)col);
           }
        }
        //Render the scene
        SDL_RenderClear(renderer);
        renderBoard(renderer, board, button);
         
        SDL_RenderPresent(renderer);
    }


    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
