#include "inc/BTN.h"


BTN_bool _BTN_draw(BTN_Button *button)
{
    if(SDL_RenderCopy(button->renderer, button->texture, &(SDL_Rect){0, 0, button->rect.w, button->rect.h}, &button->rect) < 0)
        return BTN_FALSE;

    SDL_RenderPresent(button->renderer);
    return BTN_TRUE;
}


char* _BTN_error(BTN_erroraction action, char *e)
{
    static char error[255];

    if(action == BTN_ERROR_SET && e != NULL)
        return SDL_strlcpy(error, e, 254) < SDL_strlen(e) ? NULL : error;

    return error;
}


SDL_bool _BTN_MountButton(BTN_Button *button)
{
    if(!button->renderer)
    {
        BTN_SetError("Need a renderer to mount the part of the button :: _BTN_MountButton\n");
        return SDL_FALSE;
    }
    //Creation of the texture of the button
    if(!button->texture)
    {
        button->texture = SDL_CreateTexture(button->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, button->rect.w * 2, button->rect.h);
        if(button->texture == NULL)
        {
            BTN_SetError("Can't textured the button :: _BTN_MountButton\n");
            return SDL_FALSE;
        }
        SDL_SetTextureBlendMode(button->texture, SDL_BLENDMODE_BLEND);
    }

    //It is with this texture that we will draw the different state of the button(hover, normal)
    SDL_Texture *temp = SDL_CreateTexture(button->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, button->rect.w, button->rect.h);
    if(temp == NULL)
    {
        SDL_DestroyTexture(button->texture);
        button->texture = NULL;
        BTN_SetError("Cannot textured the button :: _BTN_MountButton\n");
        return SDL_FALSE;
    }
    SDL_SetTextureBlendMode(temp, SDL_BLENDMODE_BLEND);


    SDL_Texture *renderTarget = SDL_GetRenderTarget(button->renderer);//save the default renderer target

    /*
    * First of all, let's draw the button at his normal state
    */

    //Creation of the label's texture on normal state
    SDL_Vector labelSize;
    SDL_Rect labelRect;
    SDL_Texture *labelTexture = BTN_URenderTexturedText_Blended(button->renderer, button->font, button->label, button->colors.labelColor, &labelSize);

    if(labelTexture == NULL)
    {
        SDL_DestroyTexture(button->texture);
        button->texture = NULL;
        SDL_DestroyTexture(temp);
        BTN_SetError("Cannot render the button's label :: _BTN_ConstructButton.\n");
        return SDL_FALSE;
    }

    labelRect = (SDL_Rect){(button->rect.w/2) - (labelSize.x/2), (button->rect.h/2) - (labelSize.y/2),
                            labelSize.x, labelSize.y};

    //set the render target to a temp texture
    SDL_SetRenderTarget(button->renderer, temp);

    //fill the button texture with default background color
    SDL_SetRenderDrawColor(button->renderer, SDL_ColorComponent(button->colors.backColor));
    SDL_RenderClear(button->renderer);

    //set the outline color
    SDL_SetRenderDrawColor(button->renderer, SDL_ColorComponent(button->colors.borderColor));
    SDL_RenderDrawRect(button->renderer, NULL);

    //draw the label
    SDL_RenderCopy(button->renderer, labelTexture, NULL, &labelRect);
    SDL_RenderPresent(button->renderer);

    //copy this frame to the button texture
    SDL_SetRenderTarget(button->renderer, renderTarget);
    BTN_UCopyTargetToStreamingTexture(button->renderer, temp, button->texture, 0, 0);
    SDL_DestroyTexture(labelTexture);

    /*
    * Now, let's draw the button at his hovered state
    */

    //Creation of the label's texture on hovered state
    labelTexture = BTN_URenderTexturedText_Blended(button->renderer, button->font, button->label, button->colors.labelColorOnHover, &labelSize);

    if(labelTexture == NULL)
    {
        SDL_DestroyTexture(button->texture);
        button->texture = NULL;
        SDL_DestroyTexture(temp);
        BTN_SetError("Cannot render the button's label on hover:: _BTN_MountButton.\n");
        return SDL_FALSE;
    }

    labelRect = (SDL_Rect){(button->rect.w/2) - (labelSize.x/2), (button->rect.h/2) - (labelSize.y/2),
                            labelSize.x, labelSize.y};

    //set the render target to a temp texture
    SDL_SetRenderTarget(button->renderer, temp);

    //fill the button texture with hover background color
    SDL_SetRenderDrawColor(button->renderer, SDL_ColorComponent(button->colors.backColorOnHover));
    SDL_RenderClear(button->renderer);

    //set the outline color
    SDL_SetRenderDrawColor(button->renderer, SDL_ColorComponent(button->colors.borderColorOnHover));
    SDL_RenderDrawRect(button->renderer, NULL);

    //draw the label
    SDL_RenderCopy(button->renderer, labelTexture, NULL, &labelRect);
    SDL_RenderPresent(button->renderer);

    //copy this frame to the button texture
    SDL_SetRenderTarget(button->renderer, renderTarget);
    BTN_UCopyTargetToStreamingTexture(button->renderer, temp, button->texture, button->rect.w, 0);
    SDL_DestroyTexture(labelTexture);

    return SDL_TRUE;
}


SDL_Rect BTN_GetBoundingBox(BTN_Button *button)
{
    return button->rect;
}


SDL_Rect BTN_GetBoundingBox(BTN_Button *button)
{
    return button->rect;
}


char *BTN_Setlabel(BTN_Button *button, char *label)
{
    SDL_strlcpy(button->label, label, BTN_LABEL_MAX_CHAR);
    _BTN_MountButton(button);
    _BTN_draw(button);
}


TTF_Font *BTN_SetFont(BTN_Button *button, TTF_Font *font)
{
    button->font = font;
    _BTN_MountButton(button);
    _BTN_draw(button);
}


SDL_bool BTN_setColors(BTN_Button *button, BTN_Colors *colors, short colorKey)
{
    SDL_bool modified = SDL_FALSE;

    if(colors != NULL)
    {
        if(colorKey&BTN_COLORS_KEY_BACK)
        {
            button->colors.backColor = colors->backColor;
            modified = SDL_TRUE;
        }
        if(colorKey&BTN_COLORS_KEY_HBACK)
        {
            button->colors.backColorOnHover = colors->backColorOnHover;
            modified = SDL_TRUE;
        }
        if(colorKey&BTN_COLORS_KEY_LABEL)
        {
            button->colors.labelColor = colors->labelColor;
            modified = SDL_TRUE;
        }
        if(colorKey&BTN_COLORS_KEY_HLABEL)
        {
            button->colors.labelColorOnHover = colors->labelColorOnHover;
            modified = SDL_TRUE;
        }
        if(colorKey&BTN_COLORS_KEY_BORDER)
        {
            button->colors.borderColor = colors->borderColor;
            modified = SDL_TRUE;
        }
        if(colorKey&BTN_COLORS_KEY_HBORDER)
        {
            button->colors.borderColorOnHover = colors->borderColorOnHover;
            modified = SDL_TRUE;
        }

        if(modified)
        {
            _BTN_MountButton(button);
            _BTN_draw(button);
        }
    }

    return modified;
}


void BTN_SetPosition(BTN_Button *button, Uint32 x, Uint32 y)
{
    button->rect.x = x;
    button->rect.y = y;
}


BTN_State BTN_Update(BTN_Button *button, SDL_Event *event, SDL_Rect relativeTo)
{
    if(button == NULL || button->hide == SDL_TRUE)
        return BTN_UNDEFINED;

    SDL_Point cursor = {event->button.x - relativeTo.x, event->button.y - relativeTo.y};
    BTN_State status = BTN_UNDEFINED;

    if(event->type != SDL_MOUSEBUTTONDOWN && SDL_PointInRect(&cursor, &button->rect))
    {
        status = BTN_HOVERED;

        if(button->type == BTN_BUTTON_SCALEBOX)
            SDL_RenderCopy(button->renderer, button->texture, &(SDL_Rect){button->rect.w-1, 0, button->rect.w, button->rect.h},
                           &(SDL_Rect){button->rect.x - 1, button->rect.y - 1, button->rect.w + 2, button->rect.h + 2});
        else
            SDL_RenderCopy(button->renderer, button->texture, &(SDL_Rect){button->rect.w, 0, button->rect.w, button->rect.h},
                           &button->rect);
    }
    else if(event->type == SDL_MOUSEBUTTONDOWN && SDL_PointInRect(&cursor, &button->rect))
    {
        status = BTN_CLICKED;
        SDL_RenderCopy(button->renderer, button->texture, &(SDL_Rect){0, 0, button->rect.w, button->rect.h}, &button->rect);
    }
    else
    {
        SDL_RenderCopy(button->renderer, button->texture, &(SDL_Rect){0, 0, button->rect.w, button->rect.h},
                           &button->rect);
    }
    return status;
}


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
