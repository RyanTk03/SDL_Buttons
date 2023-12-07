#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../inc/BTN_utils.h"


SDL_Texture* BTN_UCreateTextureFromPixel(SDL_Renderer *renderer, void *pixels, int w, int h, int depth, int pitch, Uint32 format)
{
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, depth, pitch, format);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}


SDL_Texture* BTN_URenderTexturedText_Blended(SDL_Renderer *render, TTF_Font *font, char *label, SDL_Color fg, SDL_Vector *labelSize)
{
    SDL_Surface *s = TTF_RenderText_Blended(font, label, fg);

    if(s == NULL)
    {
        BTN_SetError("Surface's text is NULL :: BTN_URenderTexturedText_Blended.\n");
        return NULL;
    }

    SDL_Texture *t = SDL_CreateTextureFromSurface(render, s);

    if(t == NULL)
    {
        BTN_SetError("Texture's text is NULL :: BTN_URenderTexturedText_Blended.\n");
        free(s);
        return NULL;
    }

    if(labelSize != NULL)
        labelSize->x = s->w, labelSize->y = s->h;

    SDL_FreeSurface(s);

    return t;
}


void BTN_UCopyStreamingTexture(SDL_Renderer *renderer, SDL_Texture *src, SDL_Texture *dest, int destX, int destY)
{
    int srcWidth, srcHeight;
    SDL_QueryTexture(src, NULL, NULL, &srcWidth, &srcHeight);

    void *srcPixels, *destPixels;
    int srcPitch, destPitch;

    if (SDL_LockTexture(src, NULL, &srcPixels, &srcPitch) != 0)
    {
        BTN_SetError("Cannot lock the source texture :: BTN_UCopyTexture.\n");
        return;
    }

    if (SDL_LockTexture(dest, NULL, &destPixels, &destPitch) != 0)
    {
        BTN_SetError("Cannot lock the destination texture :: BTN_UCopyTexture.\n");
        SDL_UnlockTexture(src);
        return;
    }

    for (int y = 0; y < srcHeight; ++y)
    {
        memcpy((Uint8 *)destPixels + (destY + y) * destPitch + destX * sizeof(Uint32),
               (Uint8 *)srcPixels + y * srcPitch, srcWidth * sizeof(Uint32));
    }

    // Déverrouiller les textures
    SDL_UnlockTexture(src);
    SDL_UnlockTexture(dest);
}


void BTN_UCopyTargetToStreamingTexture(SDL_Renderer *renderer, SDL_Texture *targetTexture, SDL_Texture *streamingTexture, int destX, int destY)
{
    int width, height;
    Uint32 format;
    SDL_QueryTexture(targetTexture, &format, NULL, &width, &height);

    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    if (!tempSurface)
    {
        BTN_SetError("Cannot get a surface from the target texture :: BTN_UCopyTargetToStreamingTexture.\n");
        return;
    }

    SDL_Texture *targetSaved = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, targetTexture);
    if (SDL_RenderReadPixels(renderer, NULL, format, tempSurface->pixels, tempSurface->pitch) != 0)
    {
        BTN_SetError("Cannot read the target texture pixels :: BTN_UCopyTargetToStreamingTexture.\n");
        SDL_FreeSurface(tempSurface);
        return;
    }
    SDL_SetRenderTarget(renderer, targetSaved);

    void *streamingPixels;
    int streamingPitch;
    if(SDL_LockTexture(streamingTexture, NULL, &streamingPixels, &streamingPitch) != 0)
    {
        BTN_SetError("Cannot lock the streaming texture :: BTN_UCopyTargetToStreamingTexture.\n");
        SDL_FreeSurface(tempSurface);
        return;
    }

    for (int y = 0; y < height; ++y)
    {
        memcpy((Uint8 *)streamingPixels + (destY + y) * streamingPitch + destX * sizeof(Uint32),
               (Uint8 *)tempSurface->pixels + y * tempSurface->pitch, width * sizeof(Uint32));
    }

    SDL_UnlockTexture(streamingTexture);

    SDL_FreeSurface(tempSurface);
}

