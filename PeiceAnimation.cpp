#include "SDL.h"
#include "SDL2/SDL_image.h"
#include "PeiceAnimation.h"
#include "RenderCode.h"
#include "SDL.h"
#include <iostream>

extern float frameRate;

PeiceAnimation::PeiceAnimation(int aEndLevel, int aColumn, SDL_Texture* arButton)
  : mColumn(aColumn),
    mpTexture(arButton),
    y(0),
    mFinished(false)
{
   x = getXCordinateForColumn(aColumn);
   mEndY = getYCordinateForLevel(aEndLevel);
}

void PeiceAnimation::start()
{
   mStartTime = SDL_GetTicks();
}
    
int times = 0;

void PeiceAnimation::render(SDL_Renderer *apRenderer)
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

int PeiceAnimation::getColumn() 
{
    return mColumn;
}

void PeiceAnimation::finished()
{
    mFinished = true;
}
bool PeiceAnimation::isFinished()
{
    return mFinished;
}
