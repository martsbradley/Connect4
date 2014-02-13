#ifndef PEICEANIMATION_H
#define PEICEANIMATION_H
class SDL_Texture;
class SDL_Renderer;

class PieceAnimation {
   
public: 
    PieceAnimation(int aEndLevel, int aColumn, SDL_Texture* arButton);
    void start();
    void finished();
    bool isFinished();

    void render(SDL_Renderer* apRenderer);

    int getColumn();
private:
    int mEndY; //  Where the animation stops
    int mColumn;
    SDL_Texture* mpTexture;
    Uint32 mStartTime;
    bool mFinished;


    //Moves the dot
    //void move(Uint32 deltaTicks);

    //The X and Y offsets of the dot
    float x, y;
    
    //The velocity of the dot
    float yVel;
};


int getXCordinateForColumn(int aColumnIdx);
int getYCordinateForLevel(int alevel);
#endif // PEICEANIMATION_H
