#include "SDL.h"
#include "SDL2/SDL_image.h"
#include "PeiceAnimation.h"
#include "RenderCode.h"
#include "SDL.h"

PeiceAnimation::PeiceAnimation(int aEndLevel, int aColumn, SDL_Texture* arButton)
  : mEndLevel(aEndLevel),
    mColumn(aColumn),
    mpTexture(arButton)
{
}

void PeiceAnimation::start()
{
   mStartTime = SDL_GetTicks();
}
    
void PeiceAnimation::render(SDL_Renderer *apRenderer)
{
    int seconds = ((SDL_GetTicks() - mStartTime) / 1000);
    
    renderTexture(mpTexture, apRenderer, 50 , 50*seconds);
}

int PeiceAnimation::getColumn() 
{
    return mColumn;
}
