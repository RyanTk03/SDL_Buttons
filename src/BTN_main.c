#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../inc/BTN.h"
#include "../inc/_BTN_draw.h"
#include "../inc/_BTN_error.h"
#include "../inc/_BTN_mount.h"


BTN_Button* BTN_CreateButton(Uint8 type, int w, int h, const char *label, TTF_Font *font)
{
    //Creation of an instance of the button//
    BTN_Button *button = malloc(sizeof(*button));
    if(button == NULL)
    {
        BTN_SetError("Can't create an instance of a button :: BTN_CreateButton.\n");
        return NULL;
    }

    //The font use to draw the label in the button//
    button->font = font;
    if(button->font == NULL)
    {
        BTN_SetError("Cannot find the font to use :: BTN_CreateButton.\n");
        free(button);
        return NULL;
    }

    //Set the label of the button//
    if(label == NULL)
        label = " ";

    SDL_strlcpy(button->label, label, BTN_LABEL_MAX_CHAR);

    /*
    * The colors of the buttons
    */

    //The color of the label in the button
    button->colors.labelColor = (SDL_Color){0, 0, 0, 255};

    //The background color of the button
    button->colors.backColor = (SDL_Color){255, 255, 255, 255};

    //The background color of the button on hover
    button->colors.backColorOnHover = (SDL_Color){0, 0, 255, 128};

    //The background color of the button on hover
    button->colors.borderColor = (SDL_Color){0, 0, 255, 128};

    button->rect.w = w;
    button->rect.h = h;

    button->texture = NULL;

    return button;
}

BTN_bool BTN_CopyButton(BTN_Button *button, SDL_Renderer *renderer, SDL_Point *dst)
{
    if(!renderer)
    {
        BTN_SetError("Need a renderer to render the button :: BTN_CopyButton\n");
        return BTN_FALSE;
    }
    button->renderer = renderer;

    button->rect.x = dst->x;
    button->rect.y = dst->y;

    if(!button->texture)
        if(!_BTN_MountButton(button))
            return BTN_FALSE;

    return _BTN_draw(button);
}


void BTN_FreeButton(BTN_Button *button)
{
    if(button != NULL)
    {
        if(button->texture != NULL)
            SDL_DestroyTexture(button->texture);
        free(button);
    }
}


BTN_bool BTN_SetError(char *error)
{
    return _BTN_error(BTN_ERROR_SET, error) == NULL ? BTN_FALSE : BTN_TRUE;
}


char* BTN_GetError()
{
    return _BTN_error(BTN_ERROR_GET, NULL);
}


void BTN_HideButton(BTN_Button *button, BTN_bool hide)
{
    button->hide = hide;
}
