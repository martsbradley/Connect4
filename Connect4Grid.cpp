#include "SDLGraphics.h"
#include "Connect4Grid.h"
#include "RenderCode.h"
#include "SDL.h"
#include "SDL2/SDL_image.h"
#include "PieceAnimation.h"
#include <iostream>
#include "ScoreVisitor.h"
#include "DisplayVisitor.h"
#include "assert.h"

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


  //static struct NextPiece red = NextPiece(RED, 0);
  //static struct NextPiece yellow = NextPiece(YELLOW, 0);

Connect4Grid::Connect4Grid(SDLGraphics& arGraphics)
  : mrGraphics(arGraphics),
    mpAnimation(0)
{
    mpRenderer = mrGraphics.getRenderer();
    mpRedButton = mrGraphics.loadTexture("images/redbutton.png");
    mpYellowButton =  mrGraphics.loadTexture("images/yellowbutton.png");
    mpBoardTexture =  mrGraphics.loadFromFile("images/board2.png");

  //red = NextPiece(RED, mpRedButton);
  //yellow = NextPiece(YELLOW, mpYellowButton);
  //nextPiece = red;


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


//	mBoard.addPiece((enum ColumnName) 3); //Me
//	mBoard.addPiece((enum ColumnName) 3);
//	mBoard.addPiece((enum ColumnName) 5); //Me
//	mBoard.addPiece((enum ColumnName) 4);
//	mBoard.addPiece((enum ColumnName) 3); //Me
//	mBoard.addPiece((enum ColumnName) 4);
//	mBoard.addPiece((enum ColumnName) 5); //Me
//	mBoard.addPiece((enum ColumnName) 5);
//	mBoard.addPiece((enum ColumnName) 3); //Me
//	mBoard.addPiece((enum ColumnName) 4);
//	mBoard.addPiece((enum ColumnName) 4); //Me
//	mBoard.addPiece((enum ColumnName) 5);
//	mBoard.addPiece((enum ColumnName) 2); //Me
//	mBoard.addPiece((enum ColumnName) 5);
//	mBoard.addPiece((enum ColumnName) 5); //Me
//	mBoard.addPiece((enum ColumnName) 1);
//	mBoard.addPiece((enum ColumnName) 4); //Me
//	mBoard.addPiece((enum ColumnName) 1);
	//mBoard.addPiece((enum ColumnName) 1); //Me

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
static int verticalData[] ={ 0,  1,  2,  3,  4,  5, -1,
                             6,  7,  8,  9, 10, 11, -1,
                            12, 13, 14, 15, 16, 17, -1,
                            18, 19, 20, 21, 22, 23, -1,
                            24, 25, 26, 27, 28, 29, -1,
                            30, 31, 32, 33, 34, 35, -1,
                            36, 37, 38, 39, 40, 41, -2};

#include "BoardStrength.h"
#include "TreeBuilder.h"

void Connect4Grid::renderColumn(enum ColumnName column)
{
    int columnIdx =  column;

    for (int level = 0; level < Column::MaxHeight; ++level) {
        Piece piece = mBoard.getPositionStatus(column, level);
        
        int x = getXCordinateForColumn(columnIdx);
        

        int y = getYCordinateForLevel(level);

        if (piece == RED) 
            renderTexture(mpRedButton, mpRenderer, x, y);
        else if (piece == YELLOW)
            renderTexture(mpYellowButton, mpRenderer, x, y);
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
            mBoard.addPiece((enum ColumnName)mpAnimation->getColumn());
            std::cout << "addPiece("<< (enum ColumnName)mpAnimation->getColumn() << std::endl;
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
                std::cout << "New game" << std::endl;
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
        startAnimation(col);
    }
}
void Connect4Grid::startAnimation(int col) {
    if (mpAnimation != 0 || !mBoard.canAddPiece((enum ColumnName)col)) {
        return;
    }

    int endLevel = mBoard.howManyPiecesInColumn((enum ColumnName)col);

    //std::cout << "started animation on column " << col << std::endl;

    SDL_Texture* coin = mpRedButton;

    if (mBoard.getNextPiece() == YELLOW)
    {
        coin = mpYellowButton;
    }

    mpAnimation = new PieceAnimation(endLevel, col, coin);
    mpAnimation->start();
}

void Connect4Grid::updateGame()
{
    if (mBoard.getNextPiece() == YELLOW && (mpAnimation == 0 || mpAnimation->isFinished()))
    {
        // This hard work should be removed from the event thread.
        //std::cout << "NextPiece is " << mBoard.getNextPiece() << std::endl;
        TreeBuilder tree;
        tree.buildTree(mBoard);
        //std::cout << "Tree built" << std::endl;

        ScoreVisitor visitor;
        GameState* pState = tree.getTree();
        pState->accept(visitor);
        //std::cout << "MinMaxScore " << pState->getMinMaxValue() << std::endl;

        int columnId = visitor.getBestCol();

        enum ColumnName column = (enum ColumnName)columnId;
        assert(mBoard.canAddPiece(column));

        startAnimation(column);
        if (visitor.isGameOver()) 
        {
             std::cout << "GAME OVERGAME OVERGAME OVERGAME OVERGAME OVERGAME OVERGAME OVERGAME OVERGAME OVERGAME OVERGAME OVER"  << std::endl;
        }
    }
}
