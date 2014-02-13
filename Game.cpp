#include "Game.h"
#include <iostream>
#include "SDLGraphics.h"
#include "RenderCode.h"
#include "SDL.h"
#include "SDL2/SDL_image.h"
#include "Connect4Grid.h"
#include <sstream>

//The timer
class Timer
{
private:
    //The clock time when the timer started
    int startTicks;
    
    //The ticks stored when the timer was paused
    int pausedTicks;
    
    //The timer status
    bool paused;
    bool started;
    
public:
    //Initializes variables
    Timer();
    
    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    
    //Gets the timer's time
    int get_ticks();
    
    //Checks the status of the timer
    bool is_started();
    bool is_paused();    
};

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;    
}
//Here we have the constructor initializing the variables. Nothing much to explain here.
void Timer::start()
{
    //Start the timer
    started = true;
    
    //Unpause the timer
    paused = false;
    
    //Get the current clock time
    startTicks = SDL_GetTicks();    
}
//Now when we start the timer, we set the started status to true, we unpause the timer, and we set our starting time to the current time using SDL_GetTicks().
void Timer::stop()
{
    //Stop the timer
    started = false;
    
    //Unpause the timer
    paused = false;    
}
//When we stop it, we set the started status to false and we unpause the timer.
int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }    
    }
    
    //If the timer isn't running
    return 0;    
}
//Here we have the function that gets the timer's time.

//First we check if the timer is running. If it is, we then check if the timer is paused.

//If the timer is paused, we return the time the timer had when it was paused. We'll talk about pausing/unpausing later.

//If the timer isn't paused, we return the difference in the time from when the timer started and the current time. As you can see it's the exact same formula from the last tutorial.

//If the timer was never running in the first place, the function returns 0.
void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;
    
        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}
//Now when we want to pause the timer, first we check if the timer is running and if it's not already paused. If we can pause the timer, we set the paused status to true, and store the timer's time in "pausedTicks".
void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;
    
        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;
        
        //Reset the paused ticks
        pausedTicks = 0;
    }
}
//When we want to unpause the timer, we check if the timer is paused first.

//If it is, we set the paused status to false, then set the start time to the current clock time minus the time the timer had when it was paused.

//Finally, we set "pausedTicks" to 0 for no real reason other than I don't like stray variables.
bool Timer::is_started()
{
    return started;    
}

bool Timer::is_paused()
{
    return paused;    
}


float frameRate;
    
//Timer used to calculate the frames per second
//Timer used to update the caption
static int frameCounter = 0;
static Timer fps;
static Timer update;



Game::Game(SDLGraphics& arGraphics)
  : mrGraphics(arGraphics) 
{
    mpRenderer = mrGraphics.getRenderer();
    mpGrid = new Connect4Grid(mrGraphics);
}

Game::~Game() {
    delete mpGrid;
}


void Game::play()
{
    bool quit = false;
    update.start();
    fps.start();
    while (!quit) 
    {
        quit = handleEvents();
        renderScene();
        
        // After we handle events, we apply the surface, update the screen, then increment the frameCounter counter.
        frameCounter++;
        //If a second has passed since the caption was last updated
        if (update.get_ticks() > 1000)
        {
            //The frame rate as a string
            std::stringstream caption;
            
            //Calculate the frames per second and create the string
            float frameRate = frameCounter / ( fps.get_ticks() / 1000.f );
            std::cout << "Average Frames Per Second: " <<  frameRate << std::endl;
            
            //Reset the caption
            //SDL_WM_SetCaption( caption.str().c_str(), NULL );
            
            //Restart the update timer
            update.start();
        }
    }
}

bool Game::handleEvents()
{
    bool quit = false;
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            quit = true;
        else {
            mpGrid->handleEvent(e);
        }
    }
    return quit;
}
void Game::renderScene(){
        //Render the scene
        SDL_RenderClear(mpRenderer);
        mpGrid->renderBoard();
         
        SDL_RenderPresent(mpRenderer);
}
