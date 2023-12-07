#include "../inc/BTN.h"
#include "../inc/_BTN_mount.h"


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
