#ifndef PEICEANIMATION_H
#define PEICEANIMATION_H
class SDL_Texture;
class SDL_Renderer;

class PeiceAnimation {
   
public: 
    PeiceAnimation(int aEndLevel, int aColumn, SDL_Texture* arButton);
    void start();
    void render(SDL_Renderer* apRenderer);

    int getColumn();
private:
    int mEndLevel; //  Where the animation stops
    int mColumn;
    SDL_Texture* mpTexture;
    Uint32 mStartTime;


    //Moves the dot
    void move(Uint32 deltaTicks);

    //The X and Y offsets of the dot
    float x, y;
    
    //The velocity of the dot
    float xVel, yVel;
};

#endif // PEICEANIMATION_H
