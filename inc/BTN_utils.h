#ifndef BTN_UTILLS_H_INCLUDED
#define BTN_UTILLS_H_INCLUDED

#include <SDL2/SDL.h>

#define SDL_Vector SDL_Point
#define SDL_ColorComponent(color) color.r, color.g, color.b, color.a

SDL_Texture* BTN_UCreateTextureFromPixel(SDL_Renderer *renderer, void *pixels, int w, int h, int depth, int pitch, Uint32 format);

SDL_Texture* BTN_URenderTexturedText_Blended(SDL_Renderer *render, TTF_Font *font, char *label, SDL_Color fg, SDL_Vector *labelSize);

void BTN_UCopyStreamingTexture(SDL_Renderer *renderer, SDL_Texture *src, SDL_Texture *dest, int destX, int destY);

void BTN_UCopyTargetToStreamingTexture(SDL_Renderer *renderer, SDL_Texture *targetTexture, SDL_Texture *streamingTexture, int destX, int destY);

#endif // SDL_UTILLS_H_INCLUDED
