#include "../inc/BTN_modify.h"
#include "../inc/_BTN_draw.h"
#include "../inc/_BTN_mount.h"

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
