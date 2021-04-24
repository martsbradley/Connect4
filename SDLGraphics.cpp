#include "SDLGraphics.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdexcept>
#include <iostream>
  /**
  * Log an SDL error with some error message to the output stream of our choice
  * @param os The output stream to write the message too
  * @param msg The error message to write, format will be msg error: SDL_GetError()
  */
  void logSDLError(std::ostream &os, const std::string &msg){
      os << msg << " error: " << SDL_GetError() << std::endl;
  }

  /**
  * Loads an image into a texture on the rendering device
  * @param file The image file to load
  * @param ren The renderer to load the texture onto
  * @return the loaded texture, or nullptr if something went wrong.
  */
//static SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
//    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
//    if (texture == 0)     
//        logSDLError(std::cout, "LoadTexture");
//    return texture;
//}

SDLGraphics::SDLGraphics()
 : mpWindow(0),
   mpRenderer(0)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        std::cout << SDL_GetError() << std::endl;
        throw std::logic_error(SDL_GetError());
    }


    mpWindow = SDL_CreateWindow("Simple Connect 4", 100, 100, 600, 530, SDL_WINDOW_SHOWN);
    if (mpWindow == nullptr){
        std::cout << SDL_GetError() << std::endl;
        throw std::logic_error(SDL_GetError());
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
        std::cout << SDL_GetError() << std::endl;
        throw std::logic_error(SDL_GetError());
    }
}

SDLGraphics::~SDLGraphics() {

    std::list<SDL_Texture*>::iterator it;

    for (it = textures.begin(); it != textures.end() ; it++) {
        SDL_DestroyTexture(*it);
    }

    SDL_DestroyRenderer(mpRenderer);
    SDL_DestroyWindow(mpWindow);
    SDL_Quit();
}

SDL_Renderer* SDLGraphics::getRenderer() {

    if (mpRenderer != 0){
        return mpRenderer;
    }

    mpRenderer= SDL_CreateRenderer(mpWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mpRenderer == nullptr){
        std::cout << SDL_GetError() << std::endl;
        throw std::logic_error(SDL_GetError());
    }
    return mpRenderer;
}

SDL_Texture* SDLGraphics::loadTexture(const std::string& arFileName) {
    SDL_Texture *texture = IMG_LoadTexture(mpRenderer, arFileName.c_str());
    if (texture == nullptr) {
        throw std::logic_error("Unable to load Texture");
    }

    textures.push_back(texture);
    return texture;
}

SDL_Texture* SDLGraphics::loadFromFile(const std::string& arFileName)
{
	//The final texture
	SDL_Texture* mpNewTexture = 0;

	//Load image at specified path
	SDL_Surface* pLoadedSurface = IMG_Load(arFileName.c_str());
	if (pLoadedSurface != 0)
	{
		//Color key image

		SDL_SetColorKey(pLoadedSurface, SDL_TRUE, SDL_MapRGB(pLoadedSurface->format, 0xff,0xff, 0xff));

		//Create texture from surface pixels
        mpNewTexture = SDL_CreateTextureFromSurface(mpRenderer, pLoadedSurface);
		if (mpNewTexture == NULL)
		{
			//printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
		  //int mWidth = pLoadedSurface->w;
		  //int mHeight = pLoadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(pLoadedSurface);
	}
    else
	{
    //		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
    textures.push_back(mpNewTexture);
    return mpNewTexture;
}
