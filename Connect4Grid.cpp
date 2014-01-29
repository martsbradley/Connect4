#include "SDLGraphics.h"
#include "Connect4Grid.h"
#include "RenderCode.h"
#include "SDL.h"
#include "SDL2/SDL_image.h"
#include "PeiceAnimation.h"
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


static struct NextPeice red = NextPeice(RED, 0);
static struct NextPeice yellow = NextPeice(YELLOW, 0);

Connect4Grid::Connect4Grid(SDLGraphics& arGraphics)
  : mrGraphics(arGraphics),
    mpAnimation(0)
{
    mpRenderer = mrGraphics.getRenderer();
    mpRedButton = mrGraphics.loadTexture("images/redbutton.png");
    mpYellowButton =  mrGraphics.loadTexture("images/yellowbutton.png");
    mpBoardTexture =  mrGraphics.loadFromFile("images/board2.png");

    red = NextPeice(RED, mpRedButton);
    yellow = NextPeice(YELLOW, mpYellowButton);
    nextPeice = red;

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
    if (mpAnimation)
    {
        delete mpAnimation;
    }
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
        
        int x = getXCordinateForColumn(columnIdx);
        

        int y = getYCordinateForLevel(level);

        if (piece == RED) 
            renderTexture(mpRedButton, mpRenderer, x , y);
        else if (piece == YELLOW)
            renderTexture(mpYellowButton, mpRenderer, x , y);
    }

    if (mpAnimation != 0) 
    {
       if (!mpAnimation->isFinished())
       {
           if (mpAnimation->getColumn() == column)
           {
               mpAnimation->render(mpRenderer);
           }
        }
        else 
        {
            // Animations done, add the peice to the board.
            mBoard.addPeice(nextPeice.next, (enum ColumnName)mpAnimation->getColumn());
            delete mpAnimation;
            mpAnimation = 0;
        }
    }
}

int getXCordinateForColumn(int aColumnIdx) 
{
    int x = 10 + (aColumnIdx+1) * mColumnWidth - halfColWidth - halfButtonWidth;
    return x;
}
int getYCordinateForLevel(int alevel) 
{
    int y = 10 + (6-alevel) * mColumnHeight - halfColHeight - halfButtonHeight;
    return y;
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
            case SDLK_ESCAPE:
                mBoard.reset();
                break;
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
        if (nextPeice.next == RED)
           nextPeice = yellow;
        else 
           nextPeice = red;

        if (mpAnimation == 0   /*TODO*/ /*mBoard.canAddPeice((enum ColumnName)col)*/) {
            startAnimation(col);
        }
        
    }
}
void Connect4Grid::startAnimation(int col) {
    int endLevel = mBoard.howManyPeicesInColumn((enum ColumnName)col);

    std::cout << "started animation on column " << col << std::endl;
    mpAnimation = new PeiceAnimation(endLevel, col, nextPeice.pButton);
    mpAnimation->start();
}
