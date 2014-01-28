#include "SDLGraphics.h"
#include "Connect4Grid.h"
#include "RenderCode.h"
#include "SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

struct ColPositions {
   ColPositions(int start,int end) : mStart(start), mEnd(end){}
   int mStart;
   int mEnd;
};

static int mColumnWidth;
static int mColumnHeight;
static int mButtonWidth; 
static int mButtonHeight;
static int halfColWidth;
static int halfButtonWidth;
static int halfColHeight;
static int halfButtonHeight;

static std::vector<ColPositions> myColPositions;

Connect4Grid::Connect4Grid(SDLGraphics& arGraphics)
  : mrGraphics(arGraphics) 
{
    mpRenderer = mrGraphics.getRenderer();
    mpRedButton = mrGraphics.loadTexture("images/redbutton.png");
    mpYellowButton =  mrGraphics.loadTexture("images/yellowbutton.png");
    mpBoardTexture =  mrGraphics.loadFromFile("images/board2.png");
    nextPeice = RED;

    SDL_QueryTexture(mpBoardTexture, NULL, NULL, &mColumnWidth, &mColumnHeight);
    SDL_QueryTexture(mpRedButton, NULL, NULL, &mButtonWidth, &mButtonHeight);

    halfColWidth = mColumnWidth/2;
    halfButtonWidth = mButtonWidth/2;
    
    halfColHeight = mColumnHeight/2;
    halfButtonHeight = mButtonHeight/2;


    for (int columnIdx = COLUMN0; columnIdx <=COLUMN6; columnIdx++) {
         int x = 10 + (columnIdx+1) * mColumnWidth - halfColWidth - halfButtonWidth;
         ColPositions pos(x, x+mButtonWidth);
         myColPositions.push_back(pos);
    }
}
Connect4Grid::~Connect4Grid() {
}


void Connect4Grid::renderBoardOutline(){


    for (int rowId = 0; rowId < 7; rowId++) {
        for (int colId = 0; colId < 6; colId++) {
            renderTexture(mpBoardTexture, 
                          mpRenderer, 
                          10+mColumnWidth*rowId ,
                          10+mColumnHeight*colId);
        }
    }
}

void Connect4Grid::renderColumn(enum ColumnName column)
{
    int columnIdx =  column;

    for (int level = 0; level < Column::MaxHeight; ++level) {
        Peice piece = mBoard.getPositionStatus(column, level);
        
        int x = 10 + (columnIdx+1) * mColumnWidth - halfColWidth - halfButtonWidth;

        int y = 10 + (6-level) * mColumnHeight - halfColHeight - halfButtonHeight;

        if (piece == RED) 
            renderTexture(mpRedButton, mpRenderer, x , y);
        else if (piece == YELLOW)
            renderTexture(mpYellowButton, mpRenderer, x , y);
    }
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

    renderBoardOutline();
}

void Connect4Grid::handleEvent(SDL_Event& arEvent) 
{
    unsigned int col = 10;
    if (arEvent.type == SDL_KEYDOWN) {
        switch(arEvent.key.keysym.sym) {
            case SDLK_1:
                col = COLUMN0;
                break;
            case SDLK_2:
                col = COLUMN1;
                break;
            case SDLK_3:
                col = COLUMN2;
                break;
            case SDLK_4:
                col = COLUMN3;
                break;
            case SDLK_5:
                col = COLUMN4;
                break;
            case SDLK_6:
                col = COLUMN5;
                break;
            case SDLK_7:
                col = COLUMN6;
                break;
            default: // nothing
                ;
        }
    }

    if (arEvent.type == SDL_MOUSEBUTTONDOWN) {
        int mouseXLoci= arEvent.motion.x;

        std::vector<ColPositions>::iterator it =  myColPositions.begin();

        for (int column = 0; it != myColPositions.end(); it++, column++) {
            if ( mouseXLoci >= it->mStart && mouseXLoci < it->mEnd) {
                col = column;
                break; 
            }
        }
    }

    if (col <= COLUMN6)
    {
        mBoard.addPeice(nextPeice, (enum ColumnName)col);
        if (nextPeice == RED)
           nextPeice = YELLOW;
        else 
           nextPeice = RED;
    }
}
