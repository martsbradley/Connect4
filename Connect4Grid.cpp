#include "SDLGraphics.h"
#include "Connect4Grid.h"
#include "RenderCode.h"
#include "SDL.h"
#include "SDL2/SDL_image.h"
#include "PieceAnimation.h"
#include <iostream>
#include <algorithm>
#include "ScoreVisitor.h"
#include "DisplayVisitor.h"
#include "ComputerPlayer.h"

struct ColPositions {
   ColPositions(int start,int end) : mStart(start), mEnd(end){}
   int mStart;
   int mEnd;
};

int getPositionFromColumnLevel(int aColumnIdx, int aLevel);

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
  : mrGraphics(arGraphics),
    mpAnimation(0)
{
    mpRenderer = mrGraphics.getRenderer();
    mpRedButton = mrGraphics.loadTexture("images/redbutton.png");
    mpYellowButton =  mrGraphics.loadTexture("images/yellowbutton.png");
    mpWinningButton =  mrGraphics.loadTexture("images/winningbutton.png");
    mpBoardTexture =  mrGraphics.loadFromFile("images/board2.png");

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
    mBoard.addPiece((enum ColumnName)6);
    mBoard.addPiece((enum ColumnName)2);
    mBoard.addPiece((enum ColumnName)3);
    mBoard.addPiece((enum ColumnName)2);
    mBoard.addPiece((enum ColumnName)2);
    mBoard.addPiece((enum ColumnName)0);
    mBoard.addPiece((enum ColumnName)4);
    mBoard.addPiece((enum ColumnName)5);
    mBoard.addPiece((enum ColumnName)3);
    mBoard.addPiece((enum ColumnName)2);
    mBoard.addPiece((enum ColumnName)2);
    mBoard.addPiece((enum ColumnName)1);
    mBoard.addPiece((enum ColumnName)3);
    mBoard.addPiece((enum ColumnName)3);
    mBoard.addPiece((enum ColumnName)3);
    mBoard.addPiece((enum ColumnName)0);
    mBoard.addPiece((enum ColumnName)0);
    mBoard.addPiece((enum ColumnName)3);
    mBoard.addPiece((enum ColumnName)6);
    mBoard.addPiece((enum ColumnName)2);
    mBoard.addPiece((enum ColumnName)0);
    mBoard.addPiece((enum ColumnName)5);
    mBoard.addPiece((enum ColumnName)5);
    mBoard.addPiece((enum ColumnName)0);
    mBoard.addPiece((enum ColumnName)0);
    mBoard.addPiece((enum ColumnName)6);
    mBoard.addPiece((enum ColumnName)5);
    mBoard.addPiece((enum ColumnName)6);
    mBoard.addPiece((enum ColumnName)6);
    mBoard.addPiece((enum ColumnName)5);
    mBoard.addPiece((enum ColumnName)5);
    mBoard.addPiece((enum ColumnName)1);
//    mBoard.addPiece((enum ColumnName)1);

}
Connect4Grid::~Connect4Grid() {
    if (mpAnimation)
    {
        delete mpAnimation;
    }
}


void Connect4Grid::renderWinningLine()
{
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
    std::vector<int> winnerPos;

    if (mBoard.isGameOver())
    {
        winnerPos = mBoard.getWinningPositions();
    }

    for (int level = 0; level < Column::MaxHeight; ++level) {
        Piece piece = mBoard.getPositionStatus(column, level);
        
        int x = getXCordinateForColumn(columnIdx);
        int y = getYCordinateForLevel(level);

        if (piece == Piece::RED) 
            renderTexture(mpRedButton, mpRenderer, x, y);
        else if (piece == Piece::YELLOW)
            renderTexture(mpYellowButton, mpRenderer, x, y);

        if (mBoard.isGameOver())
        {
            int position = getPositionFromColumnLevel(columnIdx, level);

            if (std::find(winnerPos.begin(), winnerPos.end(), position) != winnerPos.end())
            {
                renderTexture(mpWinningButton, mpRenderer, x, y);
            }
        }
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
            std::cout << "addPiece((enum ColumnName)"<< (enum ColumnName)mpAnimation->getColumn() << ");" << std::endl;
            mBoard.addPiece((enum ColumnName)mpAnimation->getColumn());
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

int getPositionFromColumnLevel(int aColumnIdx, int aLevel)
{
   return (5-aLevel)+(aColumnIdx*6);
}

void Connect4Grid::renderBoard()
{
    renderColumn(COLUMN0);
    renderColumn(COLUMN1);
    renderColumn(COLUMN2);
    renderColumn(COLUMN3);
    renderColumn(COLUMN4);
    renderColumn(COLUMN5);
    renderColumn(COLUMN6);
    renderBoardOutline();
    renderWinningLine();
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

    if (arEvent.type == SDL_MOUSEBUTTONDOWN) 
    {
        int mouseXLoci= arEvent.motion.x;

        std::vector<ColPositions>::iterator it =  myColPositions.begin();

        for (int column = 0; it != myColPositions.end(); it++, column++) {
            if ( mouseXLoci >= it->mStart && mouseXLoci < it->mEnd) {
                col = column;
                break; 
            }
        }
    }

    if (!mBoard.isGameOver() && col <= COLUMN6)
    {
        startAnimation(col);
    }
}
void Connect4Grid::startAnimation(int col) {
    if (mpAnimation != 0 || !mBoard.canAddPiece((enum ColumnName)col)) {
        return;
    }

    int endLevel = mBoard.howManyPiecesInColumn((enum ColumnName)col);

    SDL_Texture* coin = mpRedButton;

    if (mBoard.getNextPiece() == Piece::YELLOW)
    {
        coin = mpYellowButton;
    }

    mpAnimation = new PieceAnimation(endLevel, col, coin);
    mpAnimation->start();
}

void Connect4Grid::updateGame()
{
    if (!mBoard.isGameOver() && mBoard.getNextPiece() == Piece::YELLOW && (mpAnimation == nullptr || mpAnimation->isFinished()))
    {
        ComputerPlayer playerTwo;
        enum ColumnName column = playerTwo.takeYourTurn(mBoard);
        startAnimation(column);
    }
}
