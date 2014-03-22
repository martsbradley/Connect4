#include "SDL.h"
#include "SDL2/SDL_image.h"
#include "PieceAnimation.h"
#include "RenderCode.h"
#include "SDL.h"
#include <iostream>

extern float frameRate;

PieceAnimation::PieceAnimation(int aEndLevel, int aColumn, SDL_Texture* arButton)
  : mColumn(aColumn),
    mpTexture(arButton),
    y(0),
    mFinished(false)
{
   x = getXCordinateForColumn(aColumn);
   mEndY = getYCordinateForLevel(aEndLevel);
}

void PieceAnimation::start()
{
   mStartTime = SDL_GetTicks();
}

void PieceAnimation::render(SDL_Renderer *apRenderer)
{
    int currentTick= SDL_GetTicks();
    float secsEachDraw = (currentTick - mStartTime)/ 1000.0;
    mStartTime = currentTick;

    int pixelsPerSecond = 700;

    y += (int)(secsEachDraw * pixelsPerSecond);

    if (y >= mEndY)
    {
        finished();
    }
    else
    {
        renderTexture(mpTexture, apRenderer, x , y);
    }
}

int PieceAnimation::getColumn() 
{
    return mColumn;
}

void PieceAnimation::finished()
{
    mFinished = true;
}
bool PieceAnimation::isFinished()
{
    return mFinished;
}
