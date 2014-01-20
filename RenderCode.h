#ifndef RENDERCODE_H
#define RENDERCODE_H
struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;


void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,int w, int h);
//  void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst,
//                     SDL_Rect *clip);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,
                   SDL_Rect *clip);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

#endif // RENDERCODE_H
